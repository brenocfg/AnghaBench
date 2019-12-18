#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sample {int volume; int loop_start; int loop_length; int rel_note; int fine_tune; short* data; } ;
struct pattern {int num_channels; int num_rows; char* data; } ;
struct module {int sequence_len; int num_instruments; int num_patterns; int fast_vol_slides; int default_gvol; int default_speed; int default_tempo; int c2_rate; int gain; int num_channels; unsigned char* sequence; unsigned char* default_panning; struct pattern* patterns; struct instrument* instruments; int /*<<< orphan*/  name; } ;
struct instrument {int num_samples; int /*<<< orphan*/  name; struct sample* samples; } ;
struct data {int dummy; } ;

/* Variables and functions */
 int FP_MASK ; 
 int FP_SHIFT ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  data_ascii (struct data*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  data_sam_s16le (struct data*,int,int,short*) ; 
 int /*<<< orphan*/  data_sam_s8 (struct data*,int,int,short*) ; 
 int data_u16le (struct data*,int) ; 
 int data_u32le (struct data*,int) ; 
 int data_u8 (struct data*,int) ; 
 int /*<<< orphan*/  dispose_module (struct module*) ; 
 int log_2 (int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static struct module* module_load_s3m( struct data *data, char *message ) {
	int idx, module_data_idx, inst_offset, flags;
	int version, sixteen_bit, tune, signed_samples;
	int stereo_mode, default_pan, channel_map[ 32 ];
	int sample_offset, sample_length, loop_start, loop_length;
	int pat_offset, note_offset, row, chan, token;
	int key, ins, volume, effect, param, panning;
	char *pattern_data;
	struct instrument *instrument;
	struct sample *sample;
	struct module *module = (struct module*)calloc( 1, sizeof( struct module ) );
	if( module ) {
		data_ascii( data, 0, 28, module->name );
		module->sequence_len = data_u16le( data, 32 );
		module->num_instruments = data_u16le( data, 34 );
		module->num_patterns = data_u16le( data, 36 );
		flags = data_u16le( data, 38 );
		version = data_u16le( data, 40 );
		module->fast_vol_slides = ( ( flags & 0x40 ) == 0x40 ) || version == 0x1300;
		signed_samples = data_u16le( data, 42 ) == 1;
		if( data_u32le( data, 44 ) != 0x4d524353 ) {
			strcpy( message, "Not an S3M file!" );
			dispose_module( module );
			return NULL;
		}
		module->default_gvol = data_u8( data, 48 );
		module->default_speed = data_u8( data, 49 );
		module->default_tempo = data_u8( data, 50 );
		module->c2_rate = 8363;
		module->gain = data_u8( data, 51 ) & 0x7F;
		stereo_mode = ( data_u8( data, 51 ) & 0x80 ) == 0x80;
		default_pan = data_u8( data, 53 ) == 0xFC;
		for( idx = 0; idx < 32; idx++ ) {
			channel_map[ idx ] = -1;
			if( data_u8( data, 64 + idx ) < 16 ) {
				channel_map[ idx ] = module->num_channels++;
			}
		}
		module->sequence = (unsigned char*)calloc( module->sequence_len, sizeof( unsigned char ) );
		if( !module->sequence ){
			dispose_module( module );
			return NULL;
		}
		for( idx = 0; idx < module->sequence_len; idx++ ) {
			module->sequence[ idx ] = data_u8( data, 96 + idx );
		}
		module_data_idx = 96 + module->sequence_len;
		module->instruments = (struct instrument*)calloc( module->num_instruments + 1, sizeof( struct instrument ) );
		if( !module->instruments ) {
			dispose_module( module );
			return NULL;
		}
		instrument = &module->instruments[ 0 ];
		instrument->num_samples = 1;
		instrument->samples = (struct sample*)calloc( 1, sizeof( struct sample ) );
		if( !instrument->samples ) {
			dispose_module( module );
			return NULL;
		}
		for( ins = 1; ins <= module->num_instruments; ins++ ) {
			instrument = &module->instruments[ ins ];
			instrument->num_samples = 1;
			instrument->samples = (struct sample*)calloc( 1, sizeof( struct sample ) );
			if( !instrument->samples ) {
				dispose_module( module );
				return NULL;
			}
			sample = &instrument->samples[ 0 ];
			inst_offset = data_u16le( data, module_data_idx ) << 4;
			module_data_idx += 2;
			data_ascii( data, inst_offset + 48, 28, instrument->name );
			if( data_u8( data, inst_offset ) == 1 && data_u16le( data, inst_offset + 76 ) == 0x4353 ) {
				sample_offset = ( data_u8( data, inst_offset + 13 ) << 20 )
					+ ( data_u16le( data, inst_offset + 14 ) << 4 );
				sample_length = data_u32le( data, inst_offset + 16 );
				loop_start = data_u32le( data, inst_offset + 20 );
				loop_length = data_u32le( data, inst_offset + 24 ) - loop_start;
				sample->volume = data_u8( data, inst_offset + 28 );
				if( data_u8( data, inst_offset + 30 ) != 0 ) {
					strcpy( message, "Packed samples not supported!" );
					dispose_module( module );
					return NULL;
				}
				if( loop_start + loop_length > sample_length ) {
					loop_length = sample_length - loop_start;
				}
				if( loop_length < 1 || !( data_u8( data, inst_offset + 31 ) & 0x1 ) ) {
					loop_start = sample_length;
					loop_length = 0;
				}
				sample->loop_start = loop_start;
				sample->loop_length = loop_length;
				/* stereo = data_u8( data, inst_offset + 31 ) & 0x2; */
				sixteen_bit = data_u8( data, inst_offset + 31 ) & 0x4;
				tune = ( log_2( data_u32le( data, inst_offset + 32 ) ) - log_2( module->c2_rate ) ) * 12;
				sample->rel_note = tune >> FP_SHIFT;
				sample->fine_tune = ( tune & FP_MASK ) >> ( FP_SHIFT - 7 );
				sample->data = (short*)calloc( sample_length + 1, sizeof( short ) );
				if( sample->data ) {
					if( sixteen_bit ) {
						data_sam_s16le( data, sample_offset, sample_length, sample->data );
					} else {
						data_sam_s8( data, sample_offset, sample_length, sample->data );
					}
					if( !signed_samples ) {
						for( idx = 0; idx < sample_length; idx++ ) {
							sample->data[ idx ] = ( sample->data[ idx ] & 0xFFFF ) - 32768;
						}
					}
					sample->data[ loop_start + loop_length ] = sample->data[ loop_start ];
				} else {
					dispose_module( module );
					return NULL;
				}
			}
		}
		module->patterns = (struct pattern*)calloc( module->num_patterns, sizeof( struct pattern ) );
		if( !module->patterns ) {
			dispose_module( module );
			return NULL;
		}
		for( idx = 0; idx < module->num_patterns; idx++ ) {
			module->patterns[ idx ].num_channels = module->num_channels;
			module->patterns[ idx ].num_rows = 64;
			pattern_data = (char*)calloc( module->num_channels * 64, 5 );
			if( !pattern_data ) {
				dispose_module( module );
				return NULL;
			}
			module->patterns[ idx ].data = pattern_data;
			pat_offset = ( data_u16le( data, module_data_idx ) << 4 ) + 2;
			row = 0;
			while( row < 64 ) {
				token = data_u8( data, pat_offset++ );
				if( token ) {
					key = ins = 0;
					if( ( token & 0x20 ) == 0x20 ) {
						/* Key + Instrument.*/
						key = data_u8( data, pat_offset++ );
						ins = data_u8( data, pat_offset++ );
						if( key < 0xFE ) {
							key = ( key >> 4 ) * 12 + ( key & 0xF ) + 1;
						} else if( key == 0xFF ) {
							key = 0;
						}
					}
					volume = 0;
					if( ( token & 0x40 ) == 0x40 ) {
						/* Volume Column.*/
						volume = ( data_u8( data, pat_offset++ ) & 0x7F ) + 0x10;
						if( volume > 0x50 ) {
							volume = 0;
						}
					}
					effect = param = 0;
					if( ( token & 0x80 ) == 0x80 ) {
						/* Effect + Param.*/
						effect = data_u8( data, pat_offset++ );
						param = data_u8( data, pat_offset++ );
						if( effect < 1 || effect >= 0x40 ) {
							effect = param = 0;
						} else if( effect > 0 ) {
							effect += 0x80;
						}
					}
					chan = channel_map[ token & 0x1F ];
					if( chan >= 0 ) {
						note_offset = ( row * module->num_channels + chan ) * 5;
						pattern_data[ note_offset     ] = key;
						pattern_data[ note_offset + 1 ] = ins;
						pattern_data[ note_offset + 2 ] = volume;
						pattern_data[ note_offset + 3 ] = effect;
						pattern_data[ note_offset + 4 ] = param;
					}
				} else {
					row++;
				}
			}
			module_data_idx += 2;
		}
		module->default_panning = (unsigned char*)calloc( module->num_channels, sizeof( unsigned char ) );
		if( module->default_panning ) {
			for( chan = 0; chan < 32; chan++ ) {
				if( channel_map[ chan ] >= 0 ) {
					panning = 7;
					if( stereo_mode ) {
						panning = 12;
						if( data_u8( data, 64 + chan ) < 8 ) {
							panning = 3;
						}
					}
					if( default_pan ) {
						flags = data_u8( data, module_data_idx + chan );
						if( ( flags & 0x20 ) == 0x20 ) {
							panning = flags & 0xF;
						}
					}
					module->default_panning[ channel_map[ chan ] ] = panning * 17;
				}
			}
		} else {
			dispose_module( module );
			return NULL;
		}
	}
	return module;
}
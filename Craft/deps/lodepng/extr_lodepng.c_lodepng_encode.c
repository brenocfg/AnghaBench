#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_46__   TYPE_7__ ;
typedef  struct TYPE_45__   TYPE_3__ ;
typedef  struct TYPE_44__   TYPE_2__ ;
typedef  struct TYPE_43__   TYPE_22__ ;
typedef  struct TYPE_42__   TYPE_1__ ;
typedef  struct TYPE_41__   TYPE_15__ ;
typedef  struct TYPE_40__   TYPE_12__ ;
typedef  struct TYPE_39__   TYPE_10__ ;

/* Type definitions */
struct TYPE_42__ {unsigned char* data; size_t size; } ;
typedef  TYPE_1__ ucvector ;
struct TYPE_43__ {int windowsize; int btype; } ;
struct TYPE_46__ {TYPE_22__ zlibsettings; int /*<<< orphan*/  text_compression; scalar_t__ add_id; scalar_t__ force_palette; int /*<<< orphan*/  auto_convert; } ;
struct TYPE_40__ {scalar_t__ colortype; int palettesize; scalar_t__ key_defined; int /*<<< orphan*/  palette; int /*<<< orphan*/  bitdepth; } ;
struct TYPE_45__ {size_t text_num; char** text_keys; size_t itext_num; char** itext_keys; int /*<<< orphan*/ * unknown_chunks_size; scalar_t__* unknown_chunks_data; int /*<<< orphan*/ * itext_strings; int /*<<< orphan*/ * itext_transkeys; int /*<<< orphan*/ * itext_langtags; int /*<<< orphan*/ * text_strings; int /*<<< orphan*/  time; scalar_t__ time_defined; scalar_t__ phys_defined; scalar_t__ background_defined; TYPE_12__ color; int /*<<< orphan*/  interlace_method; } ;
struct TYPE_41__ {scalar_t__ colortype; int /*<<< orphan*/  bitdepth; } ;
struct TYPE_39__ {int interlace_method; } ;
struct TYPE_44__ {int error; TYPE_7__ encoder; TYPE_15__ info_raw; TYPE_10__ info_png; } ;
typedef  TYPE_2__ LodePNGState ;
typedef  TYPE_3__ LodePNGInfo ;

/* Variables and functions */
 int /*<<< orphan*/  CERROR_RETURN_ERROR (int,int) ; 
 int /*<<< orphan*/  LAC_NO ; 
 scalar_t__ LCT_GREY ; 
 scalar_t__ LCT_PALETTE ; 
 scalar_t__ LCT_RGB ; 
 scalar_t__ LCT_RGBA ; 
 int /*<<< orphan*/  VERSION_STRING ; 
 int addChunk_IDAT (TYPE_1__*,unsigned char*,size_t,TYPE_22__*) ; 
 int /*<<< orphan*/  addChunk_IEND (TYPE_1__*) ; 
 int /*<<< orphan*/  addChunk_IHDR (TYPE_1__*,unsigned int,unsigned int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addChunk_PLTE (TYPE_1__*,TYPE_12__*) ; 
 int /*<<< orphan*/  addChunk_bKGD (TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  addChunk_iTXt (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_22__*) ; 
 int /*<<< orphan*/  addChunk_pHYs (TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  addChunk_tEXt (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addChunk_tIME (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  addChunk_tRNS (TYPE_1__*,TYPE_12__*) ; 
 int /*<<< orphan*/  addChunk_zTXt (TYPE_1__*,char*,int /*<<< orphan*/ ,TYPE_22__*) ; 
 void* addUnknownChunks (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 void* checkColorValidity (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ getPaletteTranslucency (int /*<<< orphan*/ ,int) ; 
 int lodepng_auto_choose_color (TYPE_12__*,unsigned char const*,unsigned int,unsigned int,TYPE_15__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lodepng_color_mode_equal (TYPE_15__*,TYPE_12__*) ; 
 int lodepng_convert (unsigned char*,unsigned char const*,TYPE_12__*,TYPE_15__*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lodepng_free (unsigned char*) ; 
 unsigned int lodepng_get_bpp (TYPE_12__*) ; 
 int /*<<< orphan*/  lodepng_info_cleanup (TYPE_3__*) ; 
 int /*<<< orphan*/  lodepng_info_copy (TYPE_3__*,TYPE_10__*) ; 
 int /*<<< orphan*/  lodepng_info_init (TYPE_3__*) ; 
 scalar_t__ lodepng_malloc (size_t) ; 
 int /*<<< orphan*/  preProcessScanlines (unsigned char**,size_t*,unsigned char const*,unsigned int,unsigned int,TYPE_3__*,TYPE_7__*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  ucvector_init (TYPE_1__*) ; 
 int /*<<< orphan*/  writeSignature (TYPE_1__*) ; 

unsigned lodepng_encode(unsigned char** out, size_t* outsize,
                        const unsigned char* image, unsigned w, unsigned h,
                        LodePNGState* state)
{
  LodePNGInfo info;
  ucvector outv;
  unsigned char* data = 0; /*uncompressed version of the IDAT chunk data*/
  size_t datasize = 0;

  /*provide some proper output values if error will happen*/
  *out = 0;
  *outsize = 0;
  state->error = 0;

  lodepng_info_init(&info);
  lodepng_info_copy(&info, &state->info_png);

  if((info.color.colortype == LCT_PALETTE || state->encoder.force_palette)
      && (info.color.palettesize == 0 || info.color.palettesize > 256))
  {
    state->error = 68; /*invalid palette size, it is only allowed to be 1-256*/
    return state->error;
  }

  if(state->encoder.auto_convert != LAC_NO)
  {
    state->error = lodepng_auto_choose_color(&info.color, image, w, h, &state->info_raw,
                                             state->encoder.auto_convert);
  }
  if(state->error) return state->error;

  if(state->encoder.zlibsettings.windowsize > 32768)
  {
    CERROR_RETURN_ERROR(state->error, 60); /*error: windowsize larger than allowed*/
  }
  if(state->encoder.zlibsettings.btype > 2)
  {
    CERROR_RETURN_ERROR(state->error, 61); /*error: unexisting btype*/
  }
  if(state->info_png.interlace_method > 1)
  {
    CERROR_RETURN_ERROR(state->error, 71); /*error: unexisting interlace mode*/
  }

  state->error = checkColorValidity(info.color.colortype, info.color.bitdepth);
  if(state->error) return state->error; /*error: unexisting color type given*/
  state->error = checkColorValidity(state->info_raw.colortype, state->info_raw.bitdepth);
  if(state->error) return state->error; /*error: unexisting color type given*/

  if(!lodepng_color_mode_equal(&state->info_raw, &info.color))
  {
    unsigned char* converted;
    size_t size = (w * h * lodepng_get_bpp(&info.color) + 7) / 8;

    converted = (unsigned char*)lodepng_malloc(size);
    if(!converted && size) state->error = 83; /*alloc fail*/
    if(!state->error)
    {
      state->error = lodepng_convert(converted, image, &info.color, &state->info_raw, w, h, 0 /*fix_png*/);
    }
    if(!state->error) preProcessScanlines(&data, &datasize, converted, w, h, &info, &state->encoder);
    lodepng_free(converted);
  }
  else preProcessScanlines(&data, &datasize, image, w, h, &info, &state->encoder);

  ucvector_init(&outv);
  while(!state->error) /*while only executed once, to break on error*/
  {
#ifdef LODEPNG_COMPILE_ANCILLARY_CHUNKS
    size_t i;
#endif /*LODEPNG_COMPILE_ANCILLARY_CHUNKS*/
    /*write signature and chunks*/
    writeSignature(&outv);
    /*IHDR*/
    addChunk_IHDR(&outv, w, h, info.color.colortype, info.color.bitdepth, info.interlace_method);
#ifdef LODEPNG_COMPILE_ANCILLARY_CHUNKS
    /*unknown chunks between IHDR and PLTE*/
    if(info.unknown_chunks_data[0])
    {
      state->error = addUnknownChunks(&outv, info.unknown_chunks_data[0], info.unknown_chunks_size[0]);
      if(state->error) break;
    }
#endif /*LODEPNG_COMPILE_ANCILLARY_CHUNKS*/
    /*PLTE*/
    if(info.color.colortype == LCT_PALETTE)
    {
      addChunk_PLTE(&outv, &info.color);
    }
    if(state->encoder.force_palette && (info.color.colortype == LCT_RGB || info.color.colortype == LCT_RGBA))
    {
      addChunk_PLTE(&outv, &info.color);
    }
    /*tRNS*/
    if(info.color.colortype == LCT_PALETTE && getPaletteTranslucency(info.color.palette, info.color.palettesize) != 0)
    {
      addChunk_tRNS(&outv, &info.color);
    }
    if((info.color.colortype == LCT_GREY || info.color.colortype == LCT_RGB) && info.color.key_defined)
    {
      addChunk_tRNS(&outv, &info.color);
    }
#ifdef LODEPNG_COMPILE_ANCILLARY_CHUNKS
    /*bKGD (must come between PLTE and the IDAt chunks*/
    if(info.background_defined) addChunk_bKGD(&outv, &info);
    /*pHYs (must come before the IDAT chunks)*/
    if(info.phys_defined) addChunk_pHYs(&outv, &info);

    /*unknown chunks between PLTE and IDAT*/
    if(info.unknown_chunks_data[1])
    {
      state->error = addUnknownChunks(&outv, info.unknown_chunks_data[1], info.unknown_chunks_size[1]);
      if(state->error) break;
    }
#endif /*LODEPNG_COMPILE_ANCILLARY_CHUNKS*/
    /*IDAT (multiple IDAT chunks must be consecutive)*/
    state->error = addChunk_IDAT(&outv, data, datasize, &state->encoder.zlibsettings);
    if(state->error) break;
#ifdef LODEPNG_COMPILE_ANCILLARY_CHUNKS
    /*tIME*/
    if(info.time_defined) addChunk_tIME(&outv, &info.time);
    /*tEXt and/or zTXt*/
    for(i = 0; i < info.text_num; i++)
    {
      if(strlen(info.text_keys[i]) > 79)
      {
        state->error = 66; /*text chunk too large*/
        break;
      }
      if(strlen(info.text_keys[i]) < 1)
      {
        state->error = 67; /*text chunk too small*/
        break;
      }
      if(state->encoder.text_compression)
        addChunk_zTXt(&outv, info.text_keys[i], info.text_strings[i], &state->encoder.zlibsettings);
      else
        addChunk_tEXt(&outv, info.text_keys[i], info.text_strings[i]);
    }
    /*LodePNG version id in text chunk*/
    if(state->encoder.add_id)
    {
      unsigned alread_added_id_text = 0;
      for(i = 0; i < info.text_num; i++)
      {
        if(!strcmp(info.text_keys[i], "LodePNG"))
        {
          alread_added_id_text = 1;
          break;
        }
      }
      if(alread_added_id_text == 0)
        addChunk_tEXt(&outv, "LodePNG", VERSION_STRING); /*it's shorter as tEXt than as zTXt chunk*/
    }
    /*iTXt*/
    for(i = 0; i < info.itext_num; i++)
    {
      if(strlen(info.itext_keys[i]) > 79)
      {
        state->error = 66; /*text chunk too large*/
        break;
      }
      if(strlen(info.itext_keys[i]) < 1)
      {
        state->error = 67; /*text chunk too small*/
        break;
      }
      addChunk_iTXt(&outv, state->encoder.text_compression,
                    info.itext_keys[i], info.itext_langtags[i], info.itext_transkeys[i], info.itext_strings[i],
                    &state->encoder.zlibsettings);
    }

    /*unknown chunks between IDAT and IEND*/
    if(info.unknown_chunks_data[2])
    {
      state->error = addUnknownChunks(&outv, info.unknown_chunks_data[2], info.unknown_chunks_size[2]);
      if(state->error) break;
    }
#endif /*LODEPNG_COMPILE_ANCILLARY_CHUNKS*/
    /*IEND*/
    addChunk_IEND(&outv);

    break; /*this isn't really a while loop; no error happened so break out now!*/
  }

  lodepng_info_cleanup(&info);
  lodepng_free(data);
  /*instead of cleaning the vector up, give it to the output*/
  *out = outv.data;
  *outsize = outv.size;

  return state->error;
}
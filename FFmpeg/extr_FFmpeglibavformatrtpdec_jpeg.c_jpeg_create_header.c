#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
typedef  int uint32_t ;
struct TYPE_9__ {char* buffer; } ;
typedef  TYPE_1__ PutByteContext ;

/* Variables and functions */
 int /*<<< orphan*/  APP0 ; 
 int /*<<< orphan*/  AV_WB16 (char*,int) ; 
 int /*<<< orphan*/  DHT ; 
 int /*<<< orphan*/  DQT ; 
 int /*<<< orphan*/  DRI ; 
 int /*<<< orphan*/  SOF0 ; 
 int /*<<< orphan*/  SOI ; 
 int /*<<< orphan*/  SOS ; 
 int /*<<< orphan*/  avpriv_mjpeg_bits_ac_chrominance ; 
 int /*<<< orphan*/  avpriv_mjpeg_bits_ac_luminance ; 
 int /*<<< orphan*/  avpriv_mjpeg_bits_dc_chrominance ; 
 int /*<<< orphan*/  avpriv_mjpeg_bits_dc_luminance ; 
 int /*<<< orphan*/  avpriv_mjpeg_val_ac_chrominance ; 
 int /*<<< orphan*/  avpriv_mjpeg_val_ac_luminance ; 
 int /*<<< orphan*/  avpriv_mjpeg_val_dc ; 
 int /*<<< orphan*/  bytestream2_init_writer (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  bytestream2_put_be16 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  bytestream2_put_buffer (TYPE_1__*,char const*,int) ; 
 int /*<<< orphan*/  bytestream2_put_byte (TYPE_1__*,int) ; 
 int bytestream2_tell_p (TYPE_1__*) ; 
 scalar_t__ jpeg_create_huffman_table (TYPE_1__*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jpeg_put_marker (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jpeg_create_header(uint8_t *buf, int size, uint32_t type, uint32_t w,
                              uint32_t h, const uint8_t *qtable, int nb_qtable,
                              int dri)
{
    PutByteContext pbc;
    uint8_t *dht_size_ptr;
    int dht_size, i;

    bytestream2_init_writer(&pbc, buf, size);

    /* Convert from blocks to pixels. */
    w <<= 3;
    h <<= 3;

    /* SOI */
    jpeg_put_marker(&pbc, SOI);

    /* JFIF header */
    jpeg_put_marker(&pbc, APP0);
    bytestream2_put_be16(&pbc, 16);
    bytestream2_put_buffer(&pbc, "JFIF", 5);
    bytestream2_put_be16(&pbc, 0x0201);
    bytestream2_put_byte(&pbc, 0);
    bytestream2_put_be16(&pbc, 1);
    bytestream2_put_be16(&pbc, 1);
    bytestream2_put_byte(&pbc, 0);
    bytestream2_put_byte(&pbc, 0);

    if (dri) {
        jpeg_put_marker(&pbc, DRI);
        bytestream2_put_be16(&pbc, 4);
        bytestream2_put_be16(&pbc, dri);
    }

    /* DQT */
    jpeg_put_marker(&pbc, DQT);
    bytestream2_put_be16(&pbc, 2 + nb_qtable * (1 + 64));

    for (i = 0; i < nb_qtable; i++) {
        bytestream2_put_byte(&pbc, i);

        /* Each table is an array of 64 values given in zig-zag
         * order, identical to the format used in a JFIF DQT
         * marker segment. */
        bytestream2_put_buffer(&pbc, qtable + 64 * i, 64);
    }

    /* DHT */
    jpeg_put_marker(&pbc, DHT);
    dht_size_ptr = pbc.buffer;
    bytestream2_put_be16(&pbc, 0);

    dht_size  = 2;
    dht_size += jpeg_create_huffman_table(&pbc, 0, 0,avpriv_mjpeg_bits_dc_luminance,
                                          avpriv_mjpeg_val_dc);
    dht_size += jpeg_create_huffman_table(&pbc, 0, 1, avpriv_mjpeg_bits_dc_chrominance,
                                          avpriv_mjpeg_val_dc);
    dht_size += jpeg_create_huffman_table(&pbc, 1, 0, avpriv_mjpeg_bits_ac_luminance,
                                          avpriv_mjpeg_val_ac_luminance);
    dht_size += jpeg_create_huffman_table(&pbc, 1, 1, avpriv_mjpeg_bits_ac_chrominance,
                                          avpriv_mjpeg_val_ac_chrominance);
    AV_WB16(dht_size_ptr, dht_size);

    /* SOF0 */
    jpeg_put_marker(&pbc, SOF0);
    bytestream2_put_be16(&pbc, 17); /* size */
    bytestream2_put_byte(&pbc, 8); /* bits per component */
    bytestream2_put_be16(&pbc, h);
    bytestream2_put_be16(&pbc, w);
    bytestream2_put_byte(&pbc, 3); /* number of components */
    bytestream2_put_byte(&pbc, 1); /* component number */
    bytestream2_put_byte(&pbc, (2 << 4) | (type ? 2 : 1)); /* hsample/vsample */
    bytestream2_put_byte(&pbc, 0); /* matrix number */
    bytestream2_put_byte(&pbc, 2); /* component number */
    bytestream2_put_byte(&pbc, 1 << 4 | 1); /* hsample/vsample */
    bytestream2_put_byte(&pbc, nb_qtable == 2 ? 1 : 0); /* matrix number */
    bytestream2_put_byte(&pbc, 3); /* component number */
    bytestream2_put_byte(&pbc, 1 << 4 | 1); /* hsample/vsample */
    bytestream2_put_byte(&pbc, nb_qtable == 2 ? 1 : 0); /* matrix number */

    /* SOS */
    jpeg_put_marker(&pbc, SOS);
    bytestream2_put_be16(&pbc, 12);
    bytestream2_put_byte(&pbc, 3);
    bytestream2_put_byte(&pbc, 1);
    bytestream2_put_byte(&pbc, 0);
    bytestream2_put_byte(&pbc, 2);
    bytestream2_put_byte(&pbc, 17);
    bytestream2_put_byte(&pbc, 3);
    bytestream2_put_byte(&pbc, 17);
    bytestream2_put_byte(&pbc, 0);
    bytestream2_put_byte(&pbc, 63);
    bytestream2_put_byte(&pbc, 0);

    /* Return the length in bytes of the JPEG header. */
    return bytestream2_tell_p(&pbc);
}
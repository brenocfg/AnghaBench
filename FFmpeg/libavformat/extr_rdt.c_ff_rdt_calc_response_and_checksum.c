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

/* Variables and functions */
 int XOR_TABLE_SIZE ; 
 int /*<<< orphan*/  av_md5_sum (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  ff_data_to_hex (char*,unsigned char*,int,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,char const*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char const*) ; 

void
ff_rdt_calc_response_and_checksum(char response[41], char chksum[9],
                                  const char *challenge)
{
    int ch_len = strlen (challenge), i;
    unsigned char zres[16],
        buf[64] = { 0xa1, 0xe9, 0x14, 0x9d, 0x0e, 0x6b, 0x3b, 0x59 };
#define XOR_TABLE_SIZE 37
    static const unsigned char xor_table[XOR_TABLE_SIZE] = {
        0x05, 0x18, 0x74, 0xd0, 0x0d, 0x09, 0x02, 0x53,
        0xc0, 0x01, 0x05, 0x05, 0x67, 0x03, 0x19, 0x70,
        0x08, 0x27, 0x66, 0x10, 0x10, 0x72, 0x08, 0x09,
        0x63, 0x11, 0x03, 0x71, 0x08, 0x08, 0x70, 0x02,
        0x10, 0x57, 0x05, 0x18, 0x54 };

    /* some (length) checks */
    if (ch_len == 40) /* what a hack... */
        ch_len = 32;
    else if (ch_len > 56)
        ch_len = 56;
    memcpy(buf + 8, challenge, ch_len);

    /* xor challenge bytewise with xor_table */
    for (i = 0; i < XOR_TABLE_SIZE; i++)
        buf[8 + i] ^= xor_table[i];

    av_md5_sum(zres, buf, 64);
    ff_data_to_hex(response, zres, 16, 1);

    /* add tail */
    strcpy (response + 32, "01d0a8e3");

    /* calculate checksum */
    for (i = 0; i < 8; i++)
        chksum[i] = response[i * 4];
    chksum[8] = 0;
}
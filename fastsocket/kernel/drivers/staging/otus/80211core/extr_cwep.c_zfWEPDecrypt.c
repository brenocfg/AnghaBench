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
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  zbuf_t ;
typedef  int u8_t ;
typedef  int u32_t ;
typedef  int u16_t ;

/* Variables and functions */
 int ZM_ICV_FAILURE ; 
 int ZM_ICV_SUCCESS ; 
 int* crc32_tab ; 
 int /*<<< orphan*/  zfMemoryCopy (int*,int*,int) ; 
 int zfwBufGetSize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zmw_rx_buf_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zmw_rx_buf_writeb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 

u16_t zfWEPDecrypt(zdev_t *dev, zbuf_t *buf, u16_t offset, u8_t keyLen, u8_t* WepKey, u8_t *iv)
{
    u8_t    S[256];
    u8_t    S2[256];
    u16_t   ui;
    u16_t   i;
    u16_t   j;
    u32_t   icv_tmp;
    u32_t   *icv;
    u32_t   rxbuf_icv;
    u8_t    temp;
    u8_t    K;
    u16_t   len;
    u8_t    key[32];

    /* Retrieve IV */
    key[0] = iv[0];
    key[1] = iv[1];
    key[2] = iv[2];

    /* Append Wep Key after IV */
    zfMemoryCopy(&key[3], WepKey, keyLen);

    keyLen += 3;

    for(i = 0; i < 256; i++)
    {
        S[i] = (u8_t)i;
        S2[i] = key[i&(keyLen-1)];
    }

    j = 0;
    for(i = 0; i < 256; i++)
    {
        j = (j + S[i] + S2[i]);
        j&=255 ;

        // Swap S[i] and S[j]
        temp = S[i];
        S[i] = S[j];
        S[j] = temp;
    }

    i = j = 0;

    len = zfwBufGetSize(dev, buf);

    for (ui = offset; ui < len; ui++)
    {
        u8_t In;

        i++;
        i &= 255;
        j += S[i];
        j &= 255;

        // Swap S[i] and S[j]
        temp = S[i];
        S[i] = S[j];
        S[j] = temp;
//          temp = (S[i] + temp) & 255;
        temp += S[i];
        temp &=255;
        K = S[temp];        // Key used to Xor with input data

        In = zmw_rx_buf_readb(dev, buf, ui);

        zmw_rx_buf_writeb(dev, buf, ui, In ^ K);
    } //End of for (ui = 0; ui < Num_Bytes; ui++)

    icv = &icv_tmp;
    *icv = -1;

    for (ui = offset; ui < len - 4; ui++)
    {
        u8_t In;

        In = zmw_rx_buf_readb(dev, buf, ui);
        *icv =  (*icv>>8) ^ crc32_tab[(*icv^In)&0xff];
    }

    *icv = ~*icv;

    rxbuf_icv = (zmw_rx_buf_readb(dev, buf, len-4) |
         zmw_rx_buf_readb(dev, buf, len-3) << 8 |
         zmw_rx_buf_readb(dev, buf, len-2) << 16 |
         zmw_rx_buf_readb(dev, buf, len-1) << 24);

    if (*icv != rxbuf_icv)
    {
        return ZM_ICV_FAILURE;
    }

    return ZM_ICV_SUCCESS;
}
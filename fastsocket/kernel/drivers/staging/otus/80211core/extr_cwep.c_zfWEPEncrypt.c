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
 int* crc32_tab ; 
 int /*<<< orphan*/  zfMemoryCopy (int*,int*,int) ; 
 int zfwBufGetSize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfwBufSetSize (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int zmw_tx_buf_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zmw_tx_buf_writeb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 

void zfWEPEncrypt(zdev_t *dev, zbuf_t *buf, u8_t *snap, u16_t snapLen, u16_t offset, u8_t keyLen, u8_t* WepKey, u8_t *iv)
{
    u8_t    S[256],S2[256];
    u16_t   ui;
    u16_t   i;
    u16_t   j;
    u8_t    temp;
    u8_t    K;
    u32_t   ltemp;
    u16_t   len;
    u32_t   icv;
    u8_t    key[32];

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
        j = (j + S[i] + S2[i]) ;
        j&=255 ;

        // Swap S[i] and S[j]
        temp = S[i];
        S[i] = S[j];
        S[j] = temp;
    }

    i = j = 0;
    icv = -1;

    /* For Snap Header */
    for (ui = 0; ui < snapLen; ui++)
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

        In = snap[ui];
        icv =  (icv>>8) ^ crc32_tab[(icv^In)&0xff];

        snap[ui] = In ^ K;
        //zmw_tx_buf_writeb(dev, buf, ui, In ^ K);
    }

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

        In = zmw_tx_buf_readb(dev, buf, ui);
        icv =  (icv>>8) ^ crc32_tab[(icv^In)&0xff];

        zmw_tx_buf_writeb(dev, buf, ui, In ^ K);
    } //End of for (ui = 0; ui < Num_Bytes; ui++)

    icv = ~(icv);
    ltemp = (u32_t) icv;

    for (ui = 0; ui < 4; ui++)
    {
        i ++;
        i &= 255;
        j += S[i];
        j &= 255;

        // Swap S[i] and S[j]
        temp = S[i];
        S[i] = S[j];
        S[j] = temp;
        temp += S[i];
        temp &= 255;
        K = S[temp];        // Key used to Xor with input data

        //*Out++ = (u8_t)(ltemp ^ K)&0xff;
        zmw_tx_buf_writeb(dev, buf, len+ui, (u8_t)(ltemp ^ K)&0xff);
        ltemp >>= 8;
    }

    zfwBufSetSize(dev, buf, len+4);
}
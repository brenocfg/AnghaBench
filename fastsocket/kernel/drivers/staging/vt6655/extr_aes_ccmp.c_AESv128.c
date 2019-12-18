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
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  AddRoundKey (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MixColumns (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ShiftRows (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SubBytes (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xor_128 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void AESv128(BYTE *key, BYTE *data, BYTE *ciphertext)
{
int  i;
int  round;
BYTE TmpdataA[16];
BYTE TmpdataB[16];
BYTE abyRoundKey[16];

    for(i=0; i<16; i++)
        abyRoundKey[i] = key[i];

    for (round = 0; round < 11; round++)
    {
        if (round == 0)
        {
            xor_128(abyRoundKey, data, ciphertext);
            AddRoundKey(abyRoundKey, round);
        }
        else if (round == 10)
        {
            SubBytes(ciphertext, TmpdataA);
            ShiftRows(TmpdataA, TmpdataB);
            xor_128(TmpdataB, abyRoundKey, ciphertext);
        }
        else // round 1 ~ 9
        {
            SubBytes(ciphertext, TmpdataA);
            ShiftRows(TmpdataA, TmpdataB);
            MixColumns(&TmpdataB[0], &TmpdataA[0]);
            MixColumns(&TmpdataB[4], &TmpdataA[4]);
            MixColumns(&TmpdataB[8], &TmpdataA[8]);
            MixColumns(&TmpdataB[12], &TmpdataA[12]);
            xor_128(TmpdataA, abyRoundKey, ciphertext);
            AddRoundKey(abyRoundKey, round);
        }
    }

}
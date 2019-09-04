#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int uint32_t ;
struct TYPE_3__ {int* MDS1; int* MDS2; int* MDS3; int* MDS4; int /*<<< orphan*/  ksize; int /*<<< orphan*/  S; } ;
typedef  TYPE_1__ AVTWOFISH ;

/* Variables and functions */
 scalar_t__* MD1 ; 
 scalar_t__* MD2 ; 
 int /*<<< orphan*/  tf_h0 (size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void precomputeMDS(AVTWOFISH *cs)
{
    uint8_t y[4];
    int i;
    for (i = 0; i < 256; i++) {
        y[0] = y[1] = y[2] = y[3] = i;
    tf_h0(y, cs->S, cs->ksize);
        cs->MDS1[i] = ((uint32_t)y[0]) ^ ((uint32_t)MD1[y[0]] << 8) ^ ((uint32_t)MD2[y[0]] << 16) ^ ((uint32_t)MD2[y[0]] << 24);
        cs->MDS2[i] = ((uint32_t)MD2[y[1]]) ^ ((uint32_t)MD2[y[1]] << 8) ^ ((uint32_t)MD1[y[1]] << 16) ^ ((uint32_t)y[1] << 24);
        cs->MDS3[i] = ((uint32_t)MD1[y[2]]) ^ ((uint32_t)MD2[y[2]] << 8) ^ ((uint32_t)y[2] << 16) ^ ((uint32_t)MD2[y[2]] << 24);
        cs->MDS4[i] = ((uint32_t)MD1[y[3]]) ^ ((uint32_t)y[3] << 8) ^ ((uint32_t)MD2[y[3]] << 16) ^ ((uint32_t)MD1[y[3]] << 24);
    }
}
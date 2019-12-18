#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* count; int* state; } ;
typedef  int /*<<< orphan*/  POINTER ;
typedef  TYPE_1__ MD4_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  Encode (unsigned char*,int*,int) ; 
 int /*<<< orphan*/  MD4Update (TYPE_1__*,unsigned char*,int) ; 
 unsigned char* PADDING ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void MD4Final (unsigned char digest[16], MD4_CTX *context)
{
	unsigned char bits[8];
	unsigned int index, padLen;

	/* Save number of bits */
	Encode (bits, context->count, 8);

	/* Pad out to 56 mod 64.*/
	index = (unsigned int)((context->count[0] >> 3) & 0x3f);
	padLen = (index < 56) ? (56 - index) : (120 - index);
	MD4Update (context, PADDING, padLen);

	/* Append length (before padding) */
	MD4Update (context, bits, 8);
	
	/* Store state in digest */
	Encode (digest, context->state, 16);

	/* Zeroize sensitive information.*/
	memset ((POINTER)context, 0, sizeof (*context));
}
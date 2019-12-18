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
typedef  int /*<<< orphan*/  word2 ;
typedef  int /*<<< orphan*/  word1 ;
typedef  int /*<<< orphan*/  word0 ;
typedef  int /*<<< orphan*/  op ;

/* Variables and functions */
 int /*<<< orphan*/  bswap16 (unsigned short) ; 
 int /*<<< orphan*/  f ; 
 int /*<<< orphan*/  fwrite (unsigned short*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_op(unsigned short op, unsigned short word0, unsigned short word1, unsigned short word2)
{
	bswap16(op);
	bswap16(word0);
	bswap16(word1);
	bswap16(word2);

	fwrite(&op,    1, sizeof(op), f);
	fwrite(&word0, 1, sizeof(word0), f);
	fwrite(&word1, 1, sizeof(word1), f);
	fwrite(&word2, 1, sizeof(word2), f);
}
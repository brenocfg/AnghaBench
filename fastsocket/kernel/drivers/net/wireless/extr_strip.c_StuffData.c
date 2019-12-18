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
typedef  int __u8 ;
typedef  int __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  StuffData_FinishBlock (int) ; 
 int Stuff_CodeMask ; 
 int Stuff_CountMask ; 
#define  Stuff_Diff 131 
 int /*<<< orphan*/  Stuff_DiffZero ; 
 int Stuff_Magic ; 
 int Stuff_MaxCount ; 
#define  Stuff_NoCode 130 
#define  Stuff_Same 129 
#define  Stuff_Zero 128 

__attribute__((used)) static __u8 *StuffData(__u8 * src, __u32 length, __u8 * dst,
		       __u8 ** code_ptr_ptr)
{
	__u8 *end = src + length;
	__u8 *code_ptr = *code_ptr_ptr;
	__u8 code = Stuff_NoCode, count = 0;

	if (!length)
		return (dst);

	if (code_ptr) {
		/*
		 * Recover state from last call, if applicable
		 */
		code = (*code_ptr ^ Stuff_Magic) & Stuff_CodeMask;
		count = (*code_ptr ^ Stuff_Magic) & Stuff_CountMask;
	}

	while (src < end) {
		switch (code) {
			/* Stuff_NoCode: If no current code, select one */
		case Stuff_NoCode:
			/* Record where we're going to put this code */
			code_ptr = dst++;
			count = 0;	/* Reset the count (zero means one instance) */
			/* Tentatively start a new block */
			if (*src == 0) {
				code = Stuff_Zero;
				src++;
			} else {
				code = Stuff_Same;
				*dst++ = *src++ ^ Stuff_Magic;
			}
			/* Note: We optimistically assume run of same -- */
			/* which will be fixed later in Stuff_Same */
			/* if it turns out not to be true. */
			break;

			/* Stuff_Zero: We already have at least one zero encoded */
		case Stuff_Zero:
			/* If another zero, count it, else finish this code block */
			if (*src == 0) {
				count++;
				src++;
			} else {
				StuffData_FinishBlock(Stuff_Zero + count);
			}
			break;

			/* Stuff_Same: We already have at least one byte encoded */
		case Stuff_Same:
			/* If another one the same, count it */
			if ((*src ^ Stuff_Magic) == code_ptr[1]) {
				count++;
				src++;
				break;
			}
			/* else, this byte does not match this block. */
			/* If we already have two or more bytes encoded, finish this code block */
			if (count) {
				StuffData_FinishBlock(Stuff_Same + count);
				break;
			}
			/* else, we only have one so far, so switch to Stuff_Diff code */
			code = Stuff_Diff;
			/* and fall through to Stuff_Diff case below
			 * Note cunning cleverness here: case Stuff_Diff compares 
			 * the current character with the previous two to see if it
			 * has a run of three the same. Won't this be an error if
			 * there aren't two previous characters stored to compare with?
			 * No. Because we know the current character is *not* the same
			 * as the previous one, the first test below will necessarily
			 * fail and the send half of the "if" won't be executed.
			 */

			/* Stuff_Diff: We have at least two *different* bytes encoded */
		case Stuff_Diff:
			/* If this is a zero, must encode a Stuff_DiffZero, and begin a new block */
			if (*src == 0) {
				StuffData_FinishBlock(Stuff_DiffZero +
						      count);
			}
			/* else, if we have three in a row, it is worth starting a Stuff_Same block */
			else if ((*src ^ Stuff_Magic) == dst[-1]
				 && dst[-1] == dst[-2]) {
				/* Back off the last two characters we encoded */
				code += count - 2;
				/* Note: "Stuff_Diff + 0" is an illegal code */
				if (code == Stuff_Diff + 0) {
					code = Stuff_Same + 0;
				}
				StuffData_FinishBlock(code);
				code_ptr = dst - 2;
				/* dst[-1] already holds the correct value */
				count = 2;	/* 2 means three bytes encoded */
				code = Stuff_Same;
			}
			/* else, another different byte, so add it to the block */
			else {
				*dst++ = *src ^ Stuff_Magic;
				count++;
			}
			src++;	/* Consume the byte */
			break;
		}
		if (count == Stuff_MaxCount) {
			StuffData_FinishBlock(code + count);
		}
	}
	if (code == Stuff_NoCode) {
		*code_ptr_ptr = NULL;
	} else {
		*code_ptr_ptr = code_ptr;
		StuffData_FinishBlock(code + count);
	}
	return (dst);
}
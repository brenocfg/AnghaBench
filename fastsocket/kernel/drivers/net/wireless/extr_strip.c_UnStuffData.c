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
 int Stuff_CodeMask ; 
 int Stuff_CountMask ; 
#define  Stuff_Diff 131 
#define  Stuff_DiffZero 130 
 int Stuff_Magic ; 
#define  Stuff_Same 129 
#define  Stuff_Zero 128 

__attribute__((used)) static __u8 *UnStuffData(__u8 * src, __u8 * end, __u8 * dst,
			 __u32 dst_length)
{
	__u8 *dst_end = dst + dst_length;
	/* Sanity check */
	if (!src || !end || !dst || !dst_length)
		return (NULL);
	while (src < end && dst < dst_end) {
		int count = (*src ^ Stuff_Magic) & Stuff_CountMask;
		switch ((*src ^ Stuff_Magic) & Stuff_CodeMask) {
		case Stuff_Diff:
			if (src + 1 + count >= end)
				return (NULL);
			do {
				*dst++ = *++src ^ Stuff_Magic;
			}
			while (--count >= 0 && dst < dst_end);
			if (count < 0)
				src += 1;
			else {
				if (count == 0)
					*src = Stuff_Same ^ Stuff_Magic;
				else
					*src =
					    (Stuff_Diff +
					     count) ^ Stuff_Magic;
			}
			break;
		case Stuff_DiffZero:
			if (src + 1 + count >= end)
				return (NULL);
			do {
				*dst++ = *++src ^ Stuff_Magic;
			}
			while (--count >= 0 && dst < dst_end);
			if (count < 0)
				*src = Stuff_Zero ^ Stuff_Magic;
			else
				*src =
				    (Stuff_DiffZero + count) ^ Stuff_Magic;
			break;
		case Stuff_Same:
			if (src + 1 >= end)
				return (NULL);
			do {
				*dst++ = src[1] ^ Stuff_Magic;
			}
			while (--count >= 0 && dst < dst_end);
			if (count < 0)
				src += 2;
			else
				*src = (Stuff_Same + count) ^ Stuff_Magic;
			break;
		case Stuff_Zero:
			do {
				*dst++ = 0;
			}
			while (--count >= 0 && dst < dst_end);
			if (count < 0)
				src += 1;
			else
				*src = (Stuff_Zero + count) ^ Stuff_Magic;
			break;
		}
	}
	if (dst < dst_end)
		return (NULL);
	else
		return (src);
}
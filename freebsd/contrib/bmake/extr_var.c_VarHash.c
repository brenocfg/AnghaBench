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
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Buf_AddByte (int /*<<< orphan*/ *,char const) ; 
 char* Buf_Destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Buf_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 size_t strlen (char*) ; 

__attribute__((used)) static char *
VarHash(char *str)
{
    static const char    hexdigits[16] = "0123456789abcdef";
    Buffer         buf;
    size_t         len, len2;
    unsigned char  *ustr = (unsigned char *)str;
    unsigned int   h, k, c1, c2;

    h  = 0x971e137bU;
    c1 = 0x95543787U;
    c2 = 0x2ad7eb25U;
    len2 = strlen(str);

    for (len = len2; len; ) {
	k = 0;
	switch (len) {
	default:
	    k = (ustr[3] << 24) | (ustr[2] << 16) | (ustr[1] << 8) | ustr[0];
	    len -= 4;
	    ustr += 4;
	    break;
	case 3:
	    k |= (ustr[2] << 16);
	case 2:
	    k |= (ustr[1] << 8);
	case 1:
	    k |= ustr[0];
	    len = 0;
	}
	c1 = c1 * 5 + 0x7b7d159cU;
	c2 = c2 * 5 + 0x6bce6396U;
	k *= c1;
	k = (k << 11) ^ (k >> 21);
	k *= c2;
	h = (h << 13) ^ (h >> 19);
	h = h * 5 + 0x52dce729U;
	h ^= k;
   }
   h ^= len2;
   h *= 0x85ebca6b;
   h ^= h >> 13;
   h *= 0xc2b2ae35;
   h ^= h >> 16;

   Buf_Init(&buf, 0);
   for (len = 0; len < 8; ++len) {
       Buf_AddByte(&buf, hexdigits[h & 15]);
       h >>= 4;
   }

   return Buf_Destroy(&buf, FALSE);
}
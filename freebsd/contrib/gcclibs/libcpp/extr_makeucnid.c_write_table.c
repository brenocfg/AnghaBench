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
 unsigned int C99 ; 
 unsigned int CXX ; 
 unsigned char* combining_value ; 
 scalar_t__** decomp ; 
 unsigned int digit ; 
 unsigned int* flags ; 
 unsigned int maybe_not_NFC ; 
 unsigned int not_NFC ; 
 unsigned int not_NFKC ; 
 int /*<<< orphan*/  printf (char*,char*,char*,char*,char*,char*,char*,char*,unsigned char,unsigned int) ; 

__attribute__((used)) static void
write_table (void)
{
  unsigned i;
  unsigned last_flag = flags[0];
  bool really_safe = decomp[0][0] == 0;
  unsigned char last_combine = combining_value[0];
  
  for (i = 1; i <= 65536; i++)
    if (i == 65536
	|| (flags[i] != last_flag && ((flags[i] | last_flag) & (C99 | CXX)))
	|| really_safe != (decomp[i][0] == 0)
	|| combining_value[i] != last_combine)
      {
	printf ("{ %s|%s|%s|%s|%s|%s|%s, %3d, %#06x },\n",
		last_flag & C99 ? "C99" : "  0",
		last_flag & digit ? "DIG" : "  0",
		last_flag & CXX ? "CXX" : "  0",
		really_safe ? "CID" : "  0",
		last_flag & not_NFC ? "  0" : "NFC",
		last_flag & not_NFKC ? "  0" : "NKC",
		last_flag & maybe_not_NFC ? "CTX" : "  0",
		combining_value[i - 1],
		i - 1);
	last_flag = flags[i];
	last_combine = combining_value[0];
	really_safe = decomp[i][0] == 0;
      }
}
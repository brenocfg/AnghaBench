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
typedef  int wint_t ;

/* Variables and functions */
 int CODEUNIT (int) ; 
 int EOF ; 
 int MB_CUR_MAX ; 
 int WEOF ; 

wint_t btowc(int c)
{
	int b = (unsigned char)c;
	return b<128U ? b : (MB_CUR_MAX==1 && c!=EOF) ? CODEUNIT(c) : WEOF;
}
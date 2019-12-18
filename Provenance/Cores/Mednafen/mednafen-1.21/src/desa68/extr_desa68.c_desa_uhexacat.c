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
 int* Thex ; 
 int /*<<< orphan*/  desa_char (int) ; 

__attribute__((used)) static void desa_uhexacat(unsigned int n, int ndigit, int header_char)
{
  int shf;
  desa_char(header_char);
  for(shf=(ndigit-1)*4; shf>=0; shf-=4) {
    desa_char(Thex[(n>>shf)&15] );
  }
}
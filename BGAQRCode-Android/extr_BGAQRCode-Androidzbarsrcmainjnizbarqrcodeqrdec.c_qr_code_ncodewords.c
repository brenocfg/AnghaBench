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

__attribute__((used)) static int qr_code_ncodewords(unsigned _version){
  unsigned nalign;
  /*This is 24-27 instructions on ARM in thumb mode, or a 26-32 byte savings
     over just using a table (not counting the instructions that would be
     needed to do the table lookup).*/
  if(_version==1)return 26;
  nalign=(_version/7)+2;
  return (_version<<4)*(_version+8)
   -(5*nalign)*(5*nalign-2)+36*(_version<7)+83>>3;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  carttype; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 TYPE_1__* CartridgeArea ; 
 int StateFinishHeader (int /*<<< orphan*/ *,int) ; 
 int StateWriteHeader (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  fwrite (void*,int,int,int /*<<< orphan*/ *) ; 

int CartSaveState(FILE * fp)
{
   int offset;

   offset = StateWriteHeader(fp, "CART", 1);

   // Write cart type
   fwrite((void *)&CartridgeArea->carttype, 4, 1, fp);

   // Write the areas associated with the cart type here

   return StateFinishHeader(fp, offset);
}
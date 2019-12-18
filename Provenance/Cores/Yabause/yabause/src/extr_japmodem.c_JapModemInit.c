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
typedef  int /*<<< orphan*/  JapModem ;

/* Variables and functions */
 int /*<<< orphan*/  CART_NONE ; 
 TYPE_1__* Cs2Area ; 
 int /*<<< orphan*/ * JapModemArea ; 
 int NetlinkInit (char const*,char const*) ; 
 int /*<<< orphan*/  YAB_ERR_CANNOTINIT ; 
 int /*<<< orphan*/  YabSetError (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/ * malloc (int) ; 

int JapModemInit(const char *ip, const char *port)
{  
   if ((JapModemArea = malloc(sizeof(JapModem))) == NULL)
   {
      Cs2Area->carttype = CART_NONE;
      YabSetError(YAB_ERR_CANNOTINIT, (void *)"Japanese Modem");
      return 0;
   }

   return NetlinkInit(ip, port);
}
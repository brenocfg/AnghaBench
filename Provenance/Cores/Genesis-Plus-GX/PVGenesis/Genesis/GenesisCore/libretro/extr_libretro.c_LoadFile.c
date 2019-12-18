#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ ram; } ;
struct TYPE_7__ {scalar_t__ status; } ;
struct TYPE_5__ {int /*<<< orphan*/  boot; } ;
struct TYPE_6__ {TYPE_1__ cartridge; } ;

/* Variables and functions */
 scalar_t__ CD_OPEN ; 
 scalar_t__ NO_DISC ; 
 scalar_t__ SYSTEM_MCD ; 
 TYPE_4__ cdc ; 
 TYPE_3__ cdd ; 
 int cdd_load (char*,char*) ; 
 int /*<<< orphan*/  getrominfo (char*) ; 
 int load_rom (char*) ; 
 TYPE_2__ scd ; 
 scalar_t__ system_hw ; 

__attribute__((used)) static bool LoadFile(char * filename)
{
   int size = 0;

   /* check if virtual CD tray was open */
   if ((system_hw == SYSTEM_MCD) && (cdd.status == CD_OPEN))
   {
      /* swap CD image file */
      size = cdd_load(filename, (char *)(cdc.ram));

      /* update CD header information */
      if (!scd.cartridge.boot)
         getrominfo((char *)(cdc.ram));
   }

   /* no CD image file loaded */
   if (!size)
   {
      /* close CD tray to force system reset */
      cdd.status = NO_DISC;
      
      /* load game file */
      size = load_rom(filename);
   }

   return size > 0;
}
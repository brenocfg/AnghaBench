#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ui ;
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_6__ {int /*<<< orphan*/  fh_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  fh_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  fh_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  INVALIDID ; 
 int /*<<< orphan*/  ROOTID ; 
 int /*<<< orphan*/  SLINKID ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 TYPE_3__ root ; 
 TYPE_2__ slink ; 
 TYPE_1__ un_fhandle ; 

void
hlfsd_init_filehandles(void)
{
  u_int ui;

  ui = ROOTID;
  memcpy(root.fh_data, &ui, sizeof(ui));

  ui = SLINKID;
  memcpy(slink.fh_data, &ui, sizeof(ui));

  ui = INVALIDID;
  memcpy(un_fhandle.fh_data, &ui, sizeof(ui));
}
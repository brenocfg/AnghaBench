#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* to_shortname; char* to_longname; char* to_doc; int /*<<< orphan*/  to_mourn_inferior; int /*<<< orphan*/  to_create_inferior; int /*<<< orphan*/  to_open; } ;

/* Variables and functions */
 int /*<<< orphan*/  extended_remote_create_inferior ; 
 int /*<<< orphan*/  extended_remote_mourn ; 
 int /*<<< orphan*/  extended_remote_open ; 
 TYPE_1__ extended_remote_ops ; 
 TYPE_1__ remote_ops ; 

__attribute__((used)) static void
init_extended_remote_ops (void)
{
  extended_remote_ops = remote_ops;

  extended_remote_ops.to_shortname = "extended-remote";
  extended_remote_ops.to_longname =
    "Extended remote serial target in gdb-specific protocol";
  extended_remote_ops.to_doc =
    "Use a remote computer via a serial line, using a gdb-specific protocol.\n\
Specify the serial device it is connected to (e.g. /dev/ttya).",
    extended_remote_ops.to_open = extended_remote_open;
  extended_remote_ops.to_create_inferior = extended_remote_create_inferior;
  extended_remote_ops.to_mourn_inferior = extended_remote_mourn;
}
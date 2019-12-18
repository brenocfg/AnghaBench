#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int c_cflag; int /*<<< orphan*/  c_lflag; } ;
struct TYPE_8__ {char* driver_name; char* name; int flags; TYPE_1__ init_termios; int /*<<< orphan*/  subtype; int /*<<< orphan*/  type; int /*<<< orphan*/  minor_start; int /*<<< orphan*/  major; int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int B9600 ; 
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int /*<<< orphan*/  BT_INFO (char*) ; 
 int CLOCAL ; 
 int CREAD ; 
 int CS8 ; 
 int HUPCL ; 
 int /*<<< orphan*/  ICANON ; 
 int /*<<< orphan*/  RFCOMM_TTY_MAJOR ; 
 int /*<<< orphan*/  RFCOMM_TTY_MINOR ; 
 int /*<<< orphan*/  RFCOMM_TTY_PORTS ; 
 int /*<<< orphan*/  SERIAL_TYPE_NORMAL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int TTY_DRIVER_DYNAMIC_DEV ; 
 int TTY_DRIVER_REAL_RAW ; 
 int /*<<< orphan*/  TTY_DRIVER_TYPE_SERIAL ; 
 TYPE_2__* alloc_tty_driver (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_tty_driver (TYPE_2__*) ; 
 int /*<<< orphan*/  rfcomm_ops ; 
 TYPE_2__* rfcomm_tty_driver ; 
 scalar_t__ tty_register_driver (TYPE_2__*) ; 
 int /*<<< orphan*/  tty_set_operations (TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_1__ tty_std_termios ; 

int rfcomm_init_ttys(void)
{
	rfcomm_tty_driver = alloc_tty_driver(RFCOMM_TTY_PORTS);
	if (!rfcomm_tty_driver)
		return -1;

	rfcomm_tty_driver->owner	= THIS_MODULE;
	rfcomm_tty_driver->driver_name	= "rfcomm";
	rfcomm_tty_driver->name		= "rfcomm";
	rfcomm_tty_driver->major	= RFCOMM_TTY_MAJOR;
	rfcomm_tty_driver->minor_start	= RFCOMM_TTY_MINOR;
	rfcomm_tty_driver->type		= TTY_DRIVER_TYPE_SERIAL;
	rfcomm_tty_driver->subtype	= SERIAL_TYPE_NORMAL;
	rfcomm_tty_driver->flags	= TTY_DRIVER_REAL_RAW | TTY_DRIVER_DYNAMIC_DEV;
	rfcomm_tty_driver->init_termios	= tty_std_termios;
	rfcomm_tty_driver->init_termios.c_cflag	= B9600 | CS8 | CREAD | HUPCL | CLOCAL;
	rfcomm_tty_driver->init_termios.c_lflag &= ~ICANON;
	tty_set_operations(rfcomm_tty_driver, &rfcomm_ops);

	if (tty_register_driver(rfcomm_tty_driver)) {
		BT_ERR("Can't register RFCOMM TTY driver");
		put_tty_driver(rfcomm_tty_driver);
		return -1;
	}

	BT_INFO("RFCOMM TTY layer initialized");

	return 0;
}
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
struct parport_joypad {char saved_data; int fd; char saved_control; int /*<<< orphan*/  ident; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPRELEASE ; 
 int /*<<< orphan*/  PPWDATA ; 
 int /*<<< orphan*/  RARCH_ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void parport_free_pad(struct parport_joypad *pad)
{
   char data = pad->saved_data;

   if (ioctl(pad->fd, PPWDATA, &data) < 0)
      RARCH_ERR("[Joypad]: Failed to restore original data register on %s\n", pad->ident);

   data = pad->saved_control;
   if (ioctl(pad->fd, PPWDATA, &data) < 0)
      RARCH_ERR("[Joypad]: Failed to restore original control register on %s\n", pad->ident);

   if (ioctl(pad->fd, PPRELEASE) < 0)
      RARCH_ERR("[Joypad]: Failed to release parallel port %s\n", pad->ident);

   close(pad->fd);
   pad->fd = -1;
}
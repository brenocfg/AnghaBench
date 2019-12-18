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
struct TYPE_2__ {int /*<<< orphan*/  ident; } ;

/* Variables and functions */
 TYPE_1__ dos_joypad ; 
 int /*<<< orphan*/  dos_joypad_name (unsigned int) ; 
 int /*<<< orphan*/  input_autoconfigure_connect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dos_joypad_autodetect_add(unsigned autoconf_pad)
{
   input_autoconfigure_connect(
         dos_joypad_name(autoconf_pad),
         NULL,
         dos_joypad.ident,
         autoconf_pad,
         0,
         0
         );
}
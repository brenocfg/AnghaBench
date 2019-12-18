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
typedef  int /*<<< orphan*/  port_read_func ;
typedef  enum input_device { ____Placeholder_input_device } input_device ;

/* Variables and functions */
#define  PICO_INPUT_PAD_3BTN 129 
#define  PICO_INPUT_PAD_6BTN 128 
 int /*<<< orphan*/ ** port_readers ; 
 int /*<<< orphan*/ * read_nothing ; 
 int /*<<< orphan*/ * read_pad_3btn ; 
 int /*<<< orphan*/ * read_pad_6btn ; 

void PicoSetInputDevice(int port, enum input_device device)
{
  port_read_func *func;

  if (port < 0 || port > 2)
    return;

  switch (device) {
  case PICO_INPUT_PAD_3BTN:
    func = read_pad_3btn;
    break;

  case PICO_INPUT_PAD_6BTN:
    func = read_pad_6btn;
    break;

  default:
    func = read_nothing;
    break;
  }

  port_readers[port] = func;
}
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
typedef  int /*<<< orphan*/  tuple_t ;
struct pcmcia_device {int dummy; } ;
typedef  int /*<<< orphan*/  cisparse_t ;

/* Variables and functions */
 int pcmcia_get_first_tuple (struct pcmcia_device*,int /*<<< orphan*/ *) ; 
 int pcmcia_get_tuple_data (struct pcmcia_device*,int /*<<< orphan*/ *) ; 
 int pcmcia_parse_tuple (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
first_tuple(struct pcmcia_device *handle, tuple_t *tuple, cisparse_t *parse)
{
	int err;

	if ((err = pcmcia_get_first_tuple(handle, tuple)) == 0 &&
			(err = pcmcia_get_tuple_data(handle, tuple)) == 0)
		err = pcmcia_parse_tuple(tuple, parse);
	return err;
}
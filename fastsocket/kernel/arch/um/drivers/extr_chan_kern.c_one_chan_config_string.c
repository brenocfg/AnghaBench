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
struct chan {char* dev; TYPE_1__* ops; } ;
struct TYPE_2__ {char* type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_CHUNK (char*,int,int,char*,int) ; 

__attribute__((used)) static int one_chan_config_string(struct chan *chan, char *str, int size,
				  char **error_out)
{
	int n = 0;

	if (chan == NULL) {
		CONFIG_CHUNK(str, size, n, "none", 1);
		return n;
	}

	CONFIG_CHUNK(str, size, n, chan->ops->type, 0);

	if (chan->dev == NULL) {
		CONFIG_CHUNK(str, size, n, "", 1);
		return n;
	}

	CONFIG_CHUNK(str, size, n, ":", 0);
	CONFIG_CHUNK(str, size, n, chan->dev, 0);

	return n;
}
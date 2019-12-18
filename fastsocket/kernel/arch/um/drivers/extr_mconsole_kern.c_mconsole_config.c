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
struct TYPE_2__ {char* data; } ;
struct mc_request {TYPE_1__ request; } ;
struct mc_device {char* name; int (* config ) (char*,char**) ;int /*<<< orphan*/  get_config; } ;

/* Variables and functions */
 struct mc_device* mconsole_find_dev (char*) ; 
 int /*<<< orphan*/  mconsole_get_config (int /*<<< orphan*/ ,struct mc_request*,char*) ; 
 int /*<<< orphan*/  mconsole_reply (struct mc_request*,char*,int,int /*<<< orphan*/ ) ; 
 char* skip_spaces (char*) ; 
 size_t strlen (char*) ; 
 int stub1 (char*,char**) ; 

void mconsole_config(struct mc_request *req)
{
	struct mc_device *dev;
	char *ptr = req->request.data, *name, *error_string = "";
	int err;

	ptr += strlen("config");
	ptr = skip_spaces(ptr);
	dev = mconsole_find_dev(ptr);
	if (dev == NULL) {
		mconsole_reply(req, "Bad configuration option", 1, 0);
		return;
	}

	name = &ptr[strlen(dev->name)];
	ptr = name;
	while ((*ptr != '=') && (*ptr != '\0'))
		ptr++;

	if (*ptr == '=') {
		err = (*dev->config)(name, &error_string);
		mconsole_reply(req, error_string, err, 0);
	}
	else mconsole_get_config(dev->get_config, req, name);
}
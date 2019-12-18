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
typedef  int /*<<< orphan*/  key ;
typedef  int /*<<< orphan*/  dev ;

/* Variables and functions */
 unsigned int array_size (int*) ; 
 int /*<<< orphan*/  get_line (char*,int,char const*) ; 
 int* in_adev ; 
 int /*<<< orphan*/  in_clean_binds () ; 
 int /*<<< orphan*/  in_config_bind_key (int,char*,int,int) ; 
 int in_config_parse_dev (char*) ; 
 int /*<<< orphan*/  in_unbind_all (int,int,int) ; 
 int /*<<< orphan*/  lprintf (char*,char*) ; 
 int /*<<< orphan*/  mystrip (char*) ; 
 int parse_bind_val (char*,int*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int sscanf (char const*,char*,int*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 char* strstr (char const*,char*) ; 

void config_read_keys(const char *cfg_content)
{
	char dev[256], key[128], *act;
	const char *p;
	int bind, bindtype;
	int dev_id;

	p = cfg_content;
	while (p != NULL && (p = strstr(p, "binddev = ")) != NULL) {
		p += 10;

		get_line(dev, sizeof(dev), p);
		dev_id = in_config_parse_dev(dev);
		if (dev_id < 0) {
			printf("input: can't handle dev: %s\n", dev);
			continue;
		}

		in_unbind_all(dev_id, -1, -1);
		while ((p = strstr(p, "bind"))) {
			if (strncmp(p, "binddev = ", 10) == 0)
				break;

#ifdef ANALOG_BINDS
			if (strncmp(p, "bind_analog", 11) == 0) {
				int ret = sscanf(p, "bind_analog = %d", &bind);
				p += 11;
				if (ret != 1) {
					printf("input: parse error: %16s..\n", p);
					continue;
				}
				if ((unsigned int)bind >= array_size(in_adev)) {
					printf("input: analog id %d out of range\n", bind);
					continue;
				}
				in_adev[bind] = dev_id;
				continue;
			}
#endif

			p += 4;
			if (*p != ' ') {
				printf("input: parse error: %16s..\n", p);
				continue;
			}

			get_line(key, sizeof(key), p);
			act = strchr(key, '=');
			if (act == NULL) {
				printf("parse failed: %16s..\n", p);
				continue;
			}
			*act = 0;
			act++;
			mystrip(key);
			mystrip(act);

			bind = parse_bind_val(act, &bindtype);
			if (bind != -1 && bind != 0) {
				//printf("bind #%d '%s' %08x (%s)\n", dev_id, key, bind, act);
				in_config_bind_key(dev_id, key, bind, bindtype);
			}
			else
				lprintf("config: unhandled action \"%s\"\n", act);
		}
	}
	in_clean_binds();
}
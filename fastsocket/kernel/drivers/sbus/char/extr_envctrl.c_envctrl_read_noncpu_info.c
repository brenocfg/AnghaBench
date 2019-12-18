#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct i2c_child_t {char* mon_type; char* tables; TYPE_2__* tblprop_array; TYPE_1__* chnl_array; scalar_t__ addr; } ;
struct TYPE_4__ {int offset; int /*<<< orphan*/  scale; int /*<<< orphan*/  type; } ;
struct TYPE_3__ {scalar_t__ chnl_no; } ;

/* Variables and functions */
 int PCF8584_MAX_CHANNELS ; 
 int envctrl_i2c_data_translate (unsigned char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned char*) ; 
 unsigned char envctrl_i2c_read_8591 (unsigned char,unsigned char) ; 

__attribute__((used)) static int envctrl_read_noncpu_info(struct i2c_child_t *pchild,
				    char mon_type, unsigned char *bufdata)
{
	unsigned char data;
	int i;
	char *tbl = NULL;

	for (i = 0; i < PCF8584_MAX_CHANNELS; i++) {
		if (pchild->mon_type[i] == mon_type)
			break;
	}

	if (i >= PCF8584_MAX_CHANNELS)
		return 0;

        /* Read data from address and port. */
	data = envctrl_i2c_read_8591((unsigned char)pchild->addr,
				     (unsigned char)pchild->chnl_array[i].chnl_no);

	/* Find decoding table. */
	tbl = pchild->tables + pchild->tblprop_array[i].offset;

	return envctrl_i2c_data_translate(data, pchild->tblprop_array[i].type,
					  pchild->tblprop_array[i].scale,
					  tbl, bufdata);
}
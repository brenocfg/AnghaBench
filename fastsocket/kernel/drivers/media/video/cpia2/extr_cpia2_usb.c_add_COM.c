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
struct camera_data {int COM_len; TYPE_1__* workbuff; int /*<<< orphan*/  COM_data; } ;
struct TYPE_2__ {int* data; int length; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void add_COM(struct camera_data *cam)
{
	if(cam->COM_len > 0) {
		cam->workbuff->data[cam->workbuff->length++] = 0xFF;
		cam->workbuff->data[cam->workbuff->length++] = 0xFE;
		cam->workbuff->data[cam->workbuff->length++] = 0;
		cam->workbuff->data[cam->workbuff->length++] = cam->COM_len+2;
		memcpy(cam->workbuff->data+cam->workbuff->length,
		       cam->COM_data, cam->COM_len);
		cam->workbuff->length += cam->COM_len;
	}
}
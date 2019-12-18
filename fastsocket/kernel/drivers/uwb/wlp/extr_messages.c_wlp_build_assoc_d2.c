#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wlp_wss_info {int dummy; } ;
struct wlp_wss {int dummy; } ;
struct wlp_uuid {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  type; int /*<<< orphan*/  mux_hdr; } ;
struct wlp_frame_assoc {void* attr; int /*<<< orphan*/  msg_type; int /*<<< orphan*/  version; int /*<<< orphan*/  type; TYPE_3__ hdr; } ;
struct wlp_device_info {int /*<<< orphan*/  prim_dev_type; int /*<<< orphan*/  serial; int /*<<< orphan*/  model_nr; int /*<<< orphan*/  model_name; int /*<<< orphan*/  manufacturer; int /*<<< orphan*/  name; } ;
struct wlp_attr_wss_info {int dummy; } ;
struct wlp_attr_wlp_assc_err {int dummy; } ;
struct wlp_attr_uuid_r {int dummy; } ;
struct wlp_attr_uuid_e {int dummy; } ;
struct wlp_attr_serial {int dummy; } ;
struct wlp_attr_prim_dev_type {int dummy; } ;
struct wlp_attr_model_nr {int dummy; } ;
struct wlp_attr_model_name {int dummy; } ;
struct wlp_attr_manufacturer {int dummy; } ;
struct wlp_attr_dev_name {int dummy; } ;
struct TYPE_8__ {scalar_t__ state; int /*<<< orphan*/  name; } ;
struct wlp {TYPE_4__ wss; int /*<<< orphan*/  uuid; struct wlp_device_info* dev_info; TYPE_2__* rc; } ;
struct sk_buff {scalar_t__ data; } ;
struct device {int dummy; } ;
struct TYPE_5__ {struct device dev; } ;
struct TYPE_6__ {TYPE_1__ uwb_dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  WLP_ASSOC_D2 ; 
 int /*<<< orphan*/  WLP_ASSOC_ERROR_NONE ; 
 int /*<<< orphan*/  WLP_FRAME_ASSOCIATION ; 
 int /*<<< orphan*/  WLP_PROTOCOL_ID ; 
 int /*<<< orphan*/  WLP_VERSION ; 
 scalar_t__ WLP_WSS_STATE_ACTIVE ; 
 int __wlp_setup_device_info (struct wlp*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 struct sk_buff* dev_alloc_skb (size_t) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ wlp_set_dev_name (void*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ wlp_set_manufacturer (void*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ wlp_set_model_name (void*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ wlp_set_model_nr (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wlp_set_msg_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ wlp_set_prim_dev_type (void*,int /*<<< orphan*/ *) ; 
 scalar_t__ wlp_set_serial (void*,int /*<<< orphan*/ ,int) ; 
 size_t wlp_set_uuid_e (void*,struct wlp_uuid*) ; 
 scalar_t__ wlp_set_uuid_r (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wlp_set_version (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ wlp_set_wlp_assc_err (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ wlp_set_wss_info (void*,TYPE_4__*) ; 

__attribute__((used)) static
int wlp_build_assoc_d2(struct wlp *wlp, struct wlp_wss *wss,
		       struct sk_buff **skb, struct wlp_uuid *uuid_e)
{

	struct device *dev = &wlp->rc->uwb_dev.dev;
	int result = 0;
	struct wlp_device_info *info;
	size_t used = 0;
	struct wlp_frame_assoc *_d2;
	struct sk_buff *_skb;
	void *d2_itr;
	size_t mem_needed;

	if (wlp->dev_info == NULL) {
		result = __wlp_setup_device_info(wlp);
		if (result < 0) {
			dev_err(dev, "WLP: Unable to setup device "
				"information for D2 message.\n");
			goto error;
		}
	}
	info = wlp->dev_info;
	mem_needed = sizeof(*_d2)
		      + sizeof(struct wlp_attr_uuid_e)
		      + sizeof(struct wlp_attr_uuid_r)
		      + sizeof(struct wlp_attr_dev_name)
		      + strlen(info->name)
		      + sizeof(struct wlp_attr_manufacturer)
		      + strlen(info->manufacturer)
		      + sizeof(struct wlp_attr_model_name)
		      + strlen(info->model_name)
		      + sizeof(struct wlp_attr_model_nr)
		      + strlen(info->model_nr)
		      + sizeof(struct wlp_attr_serial)
		      + strlen(info->serial)
		      + sizeof(struct wlp_attr_prim_dev_type)
		      + sizeof(struct wlp_attr_wlp_assc_err);
	if (wlp->wss.state >= WLP_WSS_STATE_ACTIVE)
		mem_needed += sizeof(struct wlp_attr_wss_info)
			      + sizeof(struct wlp_wss_info)
			      + strlen(wlp->wss.name);
	_skb = dev_alloc_skb(mem_needed);
	if (_skb == NULL) {
		dev_err(dev, "WLP: Cannot allocate memory for association "
			"message.\n");
		result = -ENOMEM;
		goto error;
	}
	_d2 = (void *) _skb->data;
	_d2->hdr.mux_hdr = cpu_to_le16(WLP_PROTOCOL_ID);
	_d2->hdr.type = WLP_FRAME_ASSOCIATION;
	_d2->type = WLP_ASSOC_D2;

	wlp_set_version(&_d2->version, WLP_VERSION);
	wlp_set_msg_type(&_d2->msg_type, WLP_ASSOC_D2);
	d2_itr = _d2->attr;
	used = wlp_set_uuid_e(d2_itr, uuid_e);
	used += wlp_set_uuid_r(d2_itr + used, &wlp->uuid);
	if (wlp->wss.state >= WLP_WSS_STATE_ACTIVE)
		used += wlp_set_wss_info(d2_itr + used, &wlp->wss);
	used += wlp_set_dev_name(d2_itr + used, info->name,
				 strlen(info->name));
	used += wlp_set_manufacturer(d2_itr + used, info->manufacturer,
				     strlen(info->manufacturer));
	used += wlp_set_model_name(d2_itr + used, info->model_name,
				   strlen(info->model_name));
	used += wlp_set_model_nr(d2_itr + used, info->model_nr,
				 strlen(info->model_nr));
	used += wlp_set_serial(d2_itr + used, info->serial,
			       strlen(info->serial));
	used += wlp_set_prim_dev_type(d2_itr + used, &info->prim_dev_type);
	used += wlp_set_wlp_assc_err(d2_itr + used, WLP_ASSOC_ERROR_NONE);
	skb_put(_skb, sizeof(*_d2) + used);
	*skb = _skb;
error:
	return result;
}
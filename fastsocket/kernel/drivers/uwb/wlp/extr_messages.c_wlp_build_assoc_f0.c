#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
struct wlp_nonce {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  type; int /*<<< orphan*/  mux_hdr; } ;
struct wlp_frame_assoc {int /*<<< orphan*/  msg_type; int /*<<< orphan*/  version; int /*<<< orphan*/  type; TYPE_3__ hdr; } ;
struct wlp_attr_wlp_assc_err {int dummy; } ;
struct wlp_attr_rnonce {int dummy; } ;
struct wlp_attr_enonce {int dummy; } ;
struct wlp {TYPE_2__* rc; } ;
struct sk_buff {scalar_t__ data; } ;
struct device {int dummy; } ;
typedef  enum wlp_assc_error { ____Placeholder_wlp_assc_error } wlp_assc_error ;
struct TYPE_4__ {struct device dev; } ;
struct TYPE_5__ {TYPE_1__ uwb_dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  WLP_ASSOC_F0 ; 
 int /*<<< orphan*/  WLP_FRAME_ASSOCIATION ; 
 int /*<<< orphan*/  WLP_PROTOCOL_ID ; 
 int /*<<< orphan*/  WLP_VERSION ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  memset (struct wlp_nonce*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  wlp_set_enonce (struct wlp_attr_enonce*,struct wlp_nonce*) ; 
 int /*<<< orphan*/  wlp_set_msg_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlp_set_rnonce (struct wlp_attr_rnonce*,struct wlp_nonce*) ; 
 int /*<<< orphan*/  wlp_set_version (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlp_set_wlp_assc_err (struct wlp_attr_wlp_assc_err*,int) ; 

__attribute__((used)) static
int wlp_build_assoc_f0(struct wlp *wlp, struct sk_buff **skb,
		       enum wlp_assc_error error)
{
	struct device *dev = &wlp->rc->uwb_dev.dev;
	int result = -ENOMEM;
	struct {
		struct wlp_frame_assoc f0_hdr;
		struct wlp_attr_enonce enonce;
		struct wlp_attr_rnonce rnonce;
		struct wlp_attr_wlp_assc_err assc_err;
	} *f0;
	struct sk_buff *_skb;
	struct wlp_nonce tmp;

	_skb = dev_alloc_skb(sizeof(*f0));
	if (_skb == NULL) {
		dev_err(dev, "WLP: Unable to allocate memory for F0 "
			"association frame. \n");
		goto error_alloc;
	}
	f0 = (void *) _skb->data;
	f0->f0_hdr.hdr.mux_hdr = cpu_to_le16(WLP_PROTOCOL_ID);
	f0->f0_hdr.hdr.type = WLP_FRAME_ASSOCIATION;
	f0->f0_hdr.type = WLP_ASSOC_F0;
	wlp_set_version(&f0->f0_hdr.version, WLP_VERSION);
	wlp_set_msg_type(&f0->f0_hdr.msg_type, WLP_ASSOC_F0);
	memset(&tmp, 0, sizeof(tmp));
	wlp_set_enonce(&f0->enonce, &tmp);
	wlp_set_rnonce(&f0->rnonce, &tmp);
	wlp_set_wlp_assc_err(&f0->assc_err, error);
	skb_put(_skb, sizeof(*f0));
	*skb = _skb;
	result = 0;
error_alloc:
	return result;
}
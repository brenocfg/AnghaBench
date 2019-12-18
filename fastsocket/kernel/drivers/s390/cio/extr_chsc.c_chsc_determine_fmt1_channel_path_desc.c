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
struct chsc_response_struct {int /*<<< orphan*/  data; } ;
struct chp_id {int dummy; } ;
struct channel_path_desc_fmt1 {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int chsc_determine_channel_path_desc (struct chp_id,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct chsc_response_struct*) ; 
 int /*<<< orphan*/  kfree (struct chsc_response_struct*) ; 
 struct chsc_response_struct* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct channel_path_desc_fmt1*,int /*<<< orphan*/ *,int) ; 

int chsc_determine_fmt1_channel_path_desc(struct chp_id chpid,
					  struct channel_path_desc_fmt1 *desc)
{
	struct chsc_response_struct *chsc_resp;
	int ret;

	chsc_resp = kzalloc(sizeof(*chsc_resp), GFP_KERNEL);
	if (!chsc_resp)
		return -ENOMEM;
	ret = chsc_determine_channel_path_desc(chpid, 0, 0, 1, 0, chsc_resp);
	if (ret)
		goto out_free;
	memcpy(desc, &chsc_resp->data, sizeof(*desc));
out_free:
	kfree(chsc_resp);
	return ret;
}
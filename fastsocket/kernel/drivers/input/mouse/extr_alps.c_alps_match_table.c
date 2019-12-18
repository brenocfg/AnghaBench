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
struct psmouse {int dummy; } ;
struct alps_model_info {unsigned char command_mode_resp; int /*<<< orphan*/  mask0; int /*<<< orphan*/  byte0; int /*<<< orphan*/  flags; int /*<<< orphan*/  proto_version; int /*<<< orphan*/  signature; } ;
struct alps_data {int /*<<< orphan*/  mask0; int /*<<< orphan*/  byte0; int /*<<< orphan*/  flags; int /*<<< orphan*/  proto_version; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct alps_model_info*) ; 
 int EINVAL ; 
 struct alps_model_info* alps_model_data ; 
 int /*<<< orphan*/  alps_set_defaults (struct alps_data*) ; 
 int /*<<< orphan*/  memcmp (unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int alps_match_table(struct psmouse *psmouse, struct alps_data *priv,
			    unsigned char *e7, unsigned char *ec)
{
	const struct alps_model_info *model;
	int i;

	for (i = 0; i < ARRAY_SIZE(alps_model_data); i++) {
		model = &alps_model_data[i];

		if (!memcmp(e7, model->signature, sizeof(model->signature)) &&
		    (!model->command_mode_resp ||
		     model->command_mode_resp == ec[2])) {

			priv->proto_version = model->proto_version;
			alps_set_defaults(priv);

			priv->flags = model->flags;
			priv->byte0 = model->byte0;
			priv->mask0 = model->mask0;

			return 0;
		}
	}

	return -EINVAL;
}
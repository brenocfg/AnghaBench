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
typedef  void* u8 ;
struct garp_attr {int /*<<< orphan*/  data; void* dlen; void* type; int /*<<< orphan*/  state; } ;
struct garp_applicant {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GARP_APPLICANT_VO ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  garp_attr_insert (struct garp_applicant*,struct garp_attr*) ; 
 struct garp_attr* kmalloc (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,void*) ; 

__attribute__((used)) static struct garp_attr *garp_attr_create(struct garp_applicant *app,
					  const void *data, u8 len, u8 type)
{
	struct garp_attr *attr;

	attr = kmalloc(sizeof(*attr) + len, GFP_ATOMIC);
	if (!attr)
		return attr;
	attr->state = GARP_APPLICANT_VO;
	attr->type  = type;
	attr->dlen  = len;
	memcpy(attr->data, data, len);
	garp_attr_insert(app, attr);
	return attr;
}
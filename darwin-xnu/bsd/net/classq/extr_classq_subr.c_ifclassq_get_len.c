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
typedef  int /*<<< orphan*/  u_int32_t ;
struct ifclassq {int dummy; } ;
typedef  int /*<<< orphan*/  mbuf_svc_class_t ;

/* Variables and functions */
 int /*<<< orphan*/  IFCQ_LEN (struct ifclassq*) ; 
 int /*<<< orphan*/  IFCQ_LEN_SC (struct ifclassq*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  IFCQ_LOCK (struct ifclassq*) ; 
 int /*<<< orphan*/  IFCQ_UNLOCK (struct ifclassq*) ; 
 int /*<<< orphan*/  MBUF_SC_UNSPEC ; 
 int MBUF_VALID_SC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY (int) ; 

int
ifclassq_get_len(struct ifclassq *ifq, mbuf_svc_class_t sc, u_int32_t *packets,
    u_int32_t *bytes)
{
	int err = 0;

	IFCQ_LOCK(ifq);
	if (sc == MBUF_SC_UNSPEC) {
		VERIFY(packets != NULL);
		*packets = IFCQ_LEN(ifq);
	} else {
		VERIFY(MBUF_VALID_SC(sc));
		VERIFY(packets != NULL && bytes != NULL);
		IFCQ_LEN_SC(ifq, sc, packets, bytes, err);
	}
	IFCQ_UNLOCK(ifq);

	return (err);
}
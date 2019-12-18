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
typedef  scalar_t__ u16 ;
struct ip_sf_list {scalar_t__ sf_inaddr; scalar_t__* sf_count; struct ip_sf_list* sf_next; } ;
struct ip_mc_list {scalar_t__ multiaddr; scalar_t__* sfcount; struct ip_sf_list* sources; struct ip_mc_list* next; } ;
struct in_device {int /*<<< orphan*/  mc_list_lock; struct ip_mc_list* mc_list; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 scalar_t__ IPPROTO_IGMP ; 
 size_t MCAST_EXCLUDE ; 
 size_t MCAST_INCLUDE ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

int ip_check_mc(struct in_device *in_dev, __be32 mc_addr, __be32 src_addr, u16 proto)
{
	struct ip_mc_list *im;
	struct ip_sf_list *psf;
	int rv = 0;

	read_lock(&in_dev->mc_list_lock);
	for (im=in_dev->mc_list; im; im=im->next) {
		if (im->multiaddr == mc_addr)
			break;
	}
	if (im && proto == IPPROTO_IGMP) {
		rv = 1;
	} else if (im) {
		if (src_addr) {
			for (psf=im->sources; psf; psf=psf->sf_next) {
				if (psf->sf_inaddr == src_addr)
					break;
			}
			if (psf)
				rv = psf->sf_count[MCAST_INCLUDE] ||
					psf->sf_count[MCAST_EXCLUDE] !=
					im->sfcount[MCAST_EXCLUDE];
			else
				rv = im->sfcount[MCAST_EXCLUDE] != 0;
		} else
			rv = 1; /* unspecified source; tentatively allow */
	}
	read_unlock(&in_dev->mc_list_lock);
	return rv;
}
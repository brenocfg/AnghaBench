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
struct sockaddr {int dummy; } ;
struct blacklist {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
#define  BLACKLIST_ABUSIVE_BEHAVIOR 131 
#define  BLACKLIST_AUTH_FAIL 130 
#define  BLACKLIST_AUTH_OK 129 
#define  BLACKLIST_BAD_USER 128 
 int BL_ABUSE ; 
 int BL_ADD ; 
 int BL_BADUSER ; 
 int BL_DELETE ; 
 int BL_INVALID ; 
 int bl_send (struct blacklist*,int,int,struct sockaddr const*,int /*<<< orphan*/ ,char const*) ; 

int
blacklist_sa_r(struct blacklist *bl, int action, int rfd,
	const struct sockaddr *sa, socklen_t slen, const char *msg)
{
	int internal_action;

	/* internal values are not the same as user application values */
	switch (action) {
	case BLACKLIST_AUTH_FAIL:
		internal_action = BL_ADD;
		break;
	case BLACKLIST_AUTH_OK:
		internal_action = BL_DELETE;
		break;
	case BLACKLIST_ABUSIVE_BEHAVIOR:
		internal_action = BL_ABUSE;
		break;
	case BLACKLIST_BAD_USER:
		internal_action = BL_BADUSER;
		break;
	default:
		internal_action = BL_INVALID;
		break;
	}
	return bl_send(bl, internal_action, rfd, sa, slen, msg);
}
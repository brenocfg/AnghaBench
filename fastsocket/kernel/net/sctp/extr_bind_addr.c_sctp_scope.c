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
struct TYPE_2__ {int /*<<< orphan*/  sa_family; } ;
union sctp_addr {TYPE_1__ sa; } ;
struct sctp_af {int /*<<< orphan*/  (* scope ) (union sctp_addr*) ;} ;
typedef  int /*<<< orphan*/  sctp_scope_t ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_SCOPE_UNUSABLE ; 
 struct sctp_af* sctp_get_af_specific (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (union sctp_addr*) ; 

sctp_scope_t sctp_scope(const union sctp_addr *addr)
{
	struct sctp_af *af;

	af = sctp_get_af_specific(addr->sa.sa_family);
	if (!af)
		return SCTP_SCOPE_UNUSABLE;

	return af->scope((union sctp_addr *)addr);
}
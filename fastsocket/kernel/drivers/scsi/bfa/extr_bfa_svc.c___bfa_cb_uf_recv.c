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
struct bfa_uf_s {int /*<<< orphan*/  bfa; } ;
struct bfa_uf_mod_s {int /*<<< orphan*/  cbarg; int /*<<< orphan*/  (* ufrecv ) (int /*<<< orphan*/ ,struct bfa_uf_s*) ;} ;
typedef  scalar_t__ bfa_boolean_t ;

/* Variables and functions */
 struct bfa_uf_mod_s* BFA_UF_MOD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct bfa_uf_s*) ; 

__attribute__((used)) static void
__bfa_cb_uf_recv(void *cbarg, bfa_boolean_t complete)
{
	struct bfa_uf_s   *uf = cbarg;
	struct bfa_uf_mod_s *ufm = BFA_UF_MOD(uf->bfa);

	if (complete)
		ufm->ufrecv(ufm->cbarg, uf);
}
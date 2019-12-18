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
struct ts_fsm_token {scalar_t__ type; scalar_t__ recur; } ;
struct ts_fsm {unsigned int ntokens; struct ts_fsm_token* tokens; } ;
struct ts_config {int flags; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int EINVAL ; 
 struct ts_config* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct ts_config*) ; 
 scalar_t__ TS_FSM_HEAD_IGNORE ; 
 scalar_t__ TS_FSM_RECUR_MAX ; 
 scalar_t__ TS_FSM_TYPE_MAX ; 
 int TS_IGNORECASE ; 
 struct ts_config* alloc_ts_config (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct ts_fsm_token*,void const*,unsigned int) ; 
 scalar_t__* token_map ; 
 struct ts_fsm* ts_config_priv (struct ts_config*) ; 

__attribute__((used)) static struct ts_config *fsm_init(const void *pattern, unsigned int len,
				    gfp_t gfp_mask, int flags)
{
	int i, err = -EINVAL;
	struct ts_config *conf;
	struct ts_fsm *fsm;
	struct ts_fsm_token *tokens = (struct ts_fsm_token *) pattern;
	unsigned int ntokens = len / sizeof(*tokens);
	size_t priv_size = sizeof(*fsm) + len;

	if (len  % sizeof(struct ts_fsm_token) || ntokens < 1)
		goto errout;

	if (flags & TS_IGNORECASE)
		goto errout;

	for (i = 0; i < ntokens; i++) {
		struct ts_fsm_token *t = &tokens[i];

		if (t->type > TS_FSM_TYPE_MAX || t->recur > TS_FSM_RECUR_MAX)
			goto errout;

		if (t->recur == TS_FSM_HEAD_IGNORE &&
		    (i != 0 || i == (ntokens - 1)))
			goto errout;
	}

	conf = alloc_ts_config(priv_size, gfp_mask);
	if (IS_ERR(conf))
		return conf;

	conf->flags = flags;
	fsm = ts_config_priv(conf);
	fsm->ntokens = ntokens;
	memcpy(fsm->tokens, pattern, len);

	for (i = 0; i < fsm->ntokens; i++) {
		struct ts_fsm_token *t = &fsm->tokens[i];
		t->type = token_map[t->type];
	}

	return conf;

errout:
	return ERR_PTR(err);
}
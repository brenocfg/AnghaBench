#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mpc_reader ;
struct TYPE_9__ {int chap_nb; struct TYPE_9__* seek_table; int /*<<< orphan*/  si; int /*<<< orphan*/  d; int /*<<< orphan*/ * r; } ;
typedef  TYPE_1__ mpc_demux ;

/* Variables and functions */
 scalar_t__ MPC_STATUS_OK ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mpc_decoder_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpc_demux_clear_buff (TYPE_1__*) ; 
 scalar_t__ mpc_demux_header (TYPE_1__*) ; 
 scalar_t__ mpc_demux_seek_init (TYPE_1__*) ; 

mpc_demux * mpc_demux_init(mpc_reader * p_reader)
{
	mpc_demux* p_tmp = malloc(sizeof(mpc_demux));

	if (p_tmp != 0) {
		memset(p_tmp, 0, sizeof(mpc_demux));
		p_tmp->r = p_reader;
		p_tmp->chap_nb = -1;
		mpc_demux_clear_buff(p_tmp);
		if (mpc_demux_header(p_tmp) == MPC_STATUS_OK &&
				  mpc_demux_seek_init(p_tmp) == MPC_STATUS_OK) {
			p_tmp->d = mpc_decoder_init(&p_tmp->si);
		} else {
			if (p_tmp->seek_table)
				free(p_tmp->seek_table);
			free(p_tmp);
			p_tmp = 0;
		}
	}

	return p_tmp;
}
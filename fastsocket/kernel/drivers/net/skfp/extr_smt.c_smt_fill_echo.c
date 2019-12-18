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
typedef  scalar_t__ u_long ;
typedef  scalar_t__ u_char ;
struct TYPE_2__ {int p_len; } ;
struct smt_p_echo {scalar_t__* ec_data; TYPE_1__ para; } ;
struct s_smc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SK_UNUSED (struct s_smc*) ; 
 int /*<<< orphan*/  SMTSETPARA (struct smt_p_echo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMT_P_ECHODATA ; 

__attribute__((used)) static void smt_fill_echo(struct s_smc *smc, struct smt_p_echo *echo, u_long seed,
			  int len)
{
	u_char	*p ;

	SK_UNUSED(smc) ;
	SMTSETPARA(echo,SMT_P_ECHODATA) ;
	echo->para.p_len = len ;
	for (p = echo->ec_data ; len ; len--) {
		*p++ = (u_char) seed ;
		seed += 13 ;
	}
}
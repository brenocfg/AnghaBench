#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int row_count; int* shuffled_idx; int /*<<< orphan*/  sfmt; scalar_t__ rng; } ;
typedef  TYPE_1__ ccv_cnnp_dataframe_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ccmalloc (int) ; 
 int /*<<< orphan*/  gsl_ran_shuffle (scalar_t__,int*,int,int) ; 
 scalar_t__ gsl_rng_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gsl_rng_default ; 
 int /*<<< orphan*/  gsl_rng_env_setup () ; 
 int /*<<< orphan*/  gsl_rng_set (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  sfmt_genrand_shuffle (int /*<<< orphan*/ *,int*,int,int) ; 
 int /*<<< orphan*/  sfmt_init_gen_rand (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void ccv_cnnp_dataframe_shuffle(ccv_cnnp_dataframe_t* const dataframe)
{
	assert(dataframe->row_count);
	int i;
	if (!dataframe->shuffled_idx)
	{
		dataframe->shuffled_idx = (int*)ccmalloc(sizeof(int) * dataframe->row_count);
		for (i = 0; i < dataframe->row_count; i++)
			dataframe->shuffled_idx[i] = i;
#ifdef HAVE_GSL
		assert(!dataframe->rng);
		gsl_rng_env_setup();
		dataframe->rng = gsl_rng_alloc(gsl_rng_default);
		gsl_rng_set(dataframe->rng, (unsigned long int)dataframe);
#else
		sfmt_init_gen_rand(&dataframe->sfmt, (uint32_t)dataframe);
#endif
	}
#ifdef HAVE_GSL
	gsl_ran_shuffle(dataframe->rng, dataframe->shuffled_idx, dataframe->row_count, sizeof(int));
#else
	sfmt_genrand_shuffle(&dataframe->sfmt, dataframe->shuffled_idx, dataframe->row_count, sizeof(int));
#endif
}
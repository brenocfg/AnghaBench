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
typedef  int /*<<< orphan*/  ccv_file_info_t ;
typedef  int /*<<< orphan*/  ccv_dense_matrix_t ;
struct TYPE_3__ {int c; int /*<<< orphan*/  file; int /*<<< orphan*/  type; int /*<<< orphan*/ * matrix; } ;
typedef  TYPE_1__ ccv_categorized_t ;

/* Variables and functions */
 int /*<<< orphan*/  CCV_CATEGORIZED_DENSE_MATRIX ; 
 int /*<<< orphan*/  CCV_CATEGORIZED_FILE ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) inline static ccv_categorized_t ccv_categorized(int c, ccv_dense_matrix_t* matrix, ccv_file_info_t* file)
{
	assert((matrix && !file) || (!matrix && file));
	ccv_categorized_t categorized;
	categorized.c = c;
	if (matrix)
		categorized.type = CCV_CATEGORIZED_DENSE_MATRIX, categorized.matrix = matrix;
	else
		categorized.type = CCV_CATEGORIZED_FILE, categorized.file = *file;
	return categorized;
}
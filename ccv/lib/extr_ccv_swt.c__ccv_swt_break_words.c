#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int neighbors; int /*<<< orphan*/  rect; TYPE_8__** letters; } ;
typedef  TYPE_2__ ccv_textline_t ;
struct TYPE_17__ {double breakdown_ratio; } ;
typedef  TYPE_3__ ccv_swt_param_t ;
typedef  int /*<<< orphan*/  ccv_rect_t ;
typedef  int /*<<< orphan*/  ccv_dense_matrix_t ;
struct TYPE_18__ {int rnum; } ;
typedef  TYPE_4__ ccv_array_t ;
struct TYPE_15__ {scalar_t__ width; scalar_t__ x; } ;
struct TYPE_19__ {TYPE_1__ rect; } ;

/* Variables and functions */
 int CCV_32S ; 
 int CCV_C1 ; 
 int /*<<< orphan*/  _ccv_sort_letters (TYPE_8__**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ccv_swt_add_letter (TYPE_2__*,TYPE_8__*) ; 
 scalar_t__ alloca (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ccfree (TYPE_8__**) ; 
 scalar_t__ ccv_array_get (TYPE_4__*,int) ; 
 TYPE_4__* ccv_array_new (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_array_push (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ccv_dense_matrix (int,int,int,int*,int /*<<< orphan*/ ) ; 
 int ccv_max (int /*<<< orphan*/ ,scalar_t__) ; 
 int ccv_otsu (int /*<<< orphan*/ *,double*,int) ; 
 double sqrt (double) ; 

__attribute__((used)) static ccv_array_t* _ccv_swt_break_words(ccv_array_t* textline, ccv_swt_param_t params)
{
	int i, j, n = 0;
	for (i = 0; i < textline->rnum; i++)
	{
		ccv_textline_t* t = (ccv_textline_t*)ccv_array_get(textline, i);
		if (t->neighbors - 1 > n)
			n = t->neighbors - 1;
	}
	assert(n > 0);
	int* buffer = (int*)alloca(n * sizeof(int));
	ccv_array_t* words = ccv_array_new(sizeof(ccv_rect_t), textline->rnum, 0);
	for (i = 0; i < textline->rnum; i++)
	{
		ccv_textline_t* t = (ccv_textline_t*)ccv_array_get(textline, i);
		_ccv_sort_letters(t->letters, t->neighbors, 0);
		int range = 0;
		double mean = 0;
		for (j = 0; j < t->neighbors - 1; j++)
		{
			buffer[j] = ccv_max(0, t->letters[j + 1]->rect.x - (t->letters[j]->rect.x + t->letters[j]->rect.width));
			if (buffer[j] >= range)
				range = buffer[j] + 1;
			mean += buffer[j];
		}
		ccv_dense_matrix_t otsu = ccv_dense_matrix(1, t->neighbors - 1, CCV_32S | CCV_C1, buffer, 0);
		double var;
		int threshold = ccv_otsu(&otsu, &var, range);
		mean = mean / (t->neighbors - 1);
		if (sqrt(var) > mean * params.breakdown_ratio)
		{
			ccv_textline_t nt = { .neighbors = 0, .letters = 0 };
			_ccv_swt_add_letter(&nt, t->letters[0]);
			for (j = 0; j < t->neighbors - 1; j++)
			{
				if (buffer[j] > threshold)
				{
					ccv_array_push(words, &nt.rect);
					if (nt.letters)
						ccfree(nt.letters);
					nt.letters = 0;
					nt.neighbors = 0;
				}
				_ccv_swt_add_letter(&nt, t->letters[j + 1]);
			}
			ccv_array_push(words, &nt.rect);
			if (nt.letters)
				ccfree(nt.letters);
		} else {
			ccv_array_push(words, &(t->rect));
		}
	}
	return words;
}
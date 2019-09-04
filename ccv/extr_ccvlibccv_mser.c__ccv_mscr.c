#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_43__   TYPE_7__ ;
typedef  struct TYPE_42__   TYPE_6__ ;
typedef  struct TYPE_41__   TYPE_5__ ;
typedef  struct TYPE_40__   TYPE_4__ ;
typedef  struct TYPE_39__   TYPE_3__ ;
typedef  struct TYPE_38__   TYPE_2__ ;
typedef  struct TYPE_37__   TYPE_1__ ;
typedef  struct TYPE_36__   TYPE_11__ ;
typedef  struct TYPE_35__   TYPE_10__ ;

/* Type definitions */
struct TYPE_41__ {int max_evolution; int area_threshold; scalar_t__ min_margin; int min_area; int max_area; double min_diversity; int /*<<< orphan*/  edge_blur_sigma; } ;
typedef  TYPE_5__ ccv_mser_param_t ;
struct TYPE_37__ {int x; int y; } ;
struct TYPE_42__ {double chi; scalar_t__ root; struct TYPE_42__* prev; struct TYPE_42__* next; TYPE_1__ point; struct TYPE_42__* shortcut; struct TYPE_42__** node; } ;
typedef  TYPE_6__ ccv_mser_node_t ;
typedef  int /*<<< orphan*/  ccv_mser_keypoint_t ;
struct TYPE_39__ {int x; int y; } ;
struct TYPE_38__ {int x; int y; } ;
struct TYPE_43__ {scalar_t__ rank; int size; int last_mscr_area; int step_now; int last_size; scalar_t__ mscr_area; double margin; double chi; double prev_chi; int seq_no; int prev_size; int reinit; double min_slope; TYPE_6__* tail; TYPE_6__* head; TYPE_3__ min_point; TYPE_2__ max_point; } ;
typedef  TYPE_7__ ccv_mscr_root_t ;
typedef  TYPE_6__ ccv_mscr_edge_t ;
typedef  TYPE_7__ ccv_mscr_area_t ;
struct TYPE_40__ {float* f32; unsigned char* u8; } ;
struct TYPE_35__ {int rows; int cols; int /*<<< orphan*/  type; TYPE_4__ data; } ;
typedef  TYPE_10__ ccv_dense_matrix_t ;
struct TYPE_36__ {scalar_t__ rnum; int rsize; } ;
typedef  TYPE_11__ ccv_array_t ;

/* Variables and functions */
 int /*<<< orphan*/  CCV_32F ; 
 int CHI_TABLE_SIZE ; 
 double DBL_MAX ; 
 int /*<<< orphan*/  _ccv_mscr_chi (TYPE_10__*,TYPE_10__**,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  _ccv_mscr_edge_qsort (TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ccv_mscr_init_root (TYPE_7__*,TYPE_6__*) ; 
 TYPE_6__* _ccv_mser_find_root (TYPE_6__*) ; 
 int /*<<< orphan*/  _ccv_mser_init_node (TYPE_6__*,int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ccfree (TYPE_6__*) ; 
 scalar_t__ ccmalloc (int) ; 
 int /*<<< orphan*/  ccv_array_free (TYPE_11__*) ; 
 scalar_t__ ccv_array_get (TYPE_11__*,scalar_t__) ; 
 TYPE_11__* ccv_array_new (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_array_push (TYPE_11__*,TYPE_7__*) ; 
 int /*<<< orphan*/  ccv_blur (TYPE_10__*,TYPE_10__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_matrix_free (TYPE_10__*) ; 
 int /*<<< orphan*/  ccv_matrix_setter_getter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* ccv_max (int,int) ; 
 void* ccv_min (int,int) ; 
 int /*<<< orphan*/  ccv_zero (TYPE_10__*) ; 
 double* chitab3 ; 
 int /*<<< orphan*/  for_block ; 

__attribute__((used)) static void _ccv_mscr(ccv_dense_matrix_t* a, ccv_dense_matrix_t* h, ccv_dense_matrix_t* b, ccv_array_t* seq, ccv_mser_param_t params)
{
	/* using 8-neighbor, as the inventor does for his default implementation */
	ccv_dense_matrix_t* dx = 0;
	_ccv_mscr_chi(a, &dx, CCV_32F, 1, 0);
	ccv_dense_matrix_t* bdx = 0;
	ccv_blur(dx, &bdx, 0, params.edge_blur_sigma);
	ccv_matrix_free(dx);
	ccv_dense_matrix_t* dy = 0;
	_ccv_mscr_chi(a, &dy, CCV_32F, 0, 1);
	ccv_dense_matrix_t* bdy = 0;
	ccv_blur(dy, &bdy, 0, params.edge_blur_sigma);
	ccv_matrix_free(dy);
	ccv_dense_matrix_t* dxy = 0;
	_ccv_mscr_chi(a, &dxy, CCV_32F, 1, 1);
	ccv_dense_matrix_t* bdxy = 0;
	ccv_blur(dxy, &bdxy, 0, params.edge_blur_sigma);
	ccv_matrix_free(dxy);
	ccv_dense_matrix_t* dxy2 = 0;
	_ccv_mscr_chi(a, &dxy2, CCV_32F, 1, -1);
	ccv_dense_matrix_t* bdxy2 = 0;
	ccv_blur(dxy2, &bdxy2, 0, params.edge_blur_sigma);
	ccv_matrix_free(dxy2);
	int i, j;
	ccv_mser_node_t* node = (ccv_mser_node_t*)ccmalloc(sizeof(ccv_mser_node_t) * a->rows * a->cols);
	ccv_mscr_edge_t* edge = (ccv_mscr_edge_t*)ccmalloc(sizeof(ccv_mscr_edge_t) * (bdx->rows * bdx->cols + bdy->rows * bdy->cols + bdxy->rows * bdxy->cols + bdxy2->rows * bdxy2->cols));
	ccv_mser_node_t* pnode = node;
	ccv_mscr_edge_t* pedge = edge;
	/* generate edge graph and sort them */
	double mean = 0;
	float* bdx_ptr = bdx->data.f32;
	assert(bdx->cols == a->cols - 1);
	for (i = 0; i < bdx->rows; i++)
	{
		for (j = 0; j < bdx->cols; j++)
		{
			mean += pedge->chi = bdx_ptr[j];
			pedge->node[0] = pnode + j;
			pedge->node[1] = pnode + j + 1;
			_ccv_mser_init_node(pnode + j, j, i); // init node in this for-loop
			++pedge;
		}
		_ccv_mser_init_node(pnode + bdx->cols, bdx->cols, i);
		pnode += a->cols;
		bdx_ptr += bdx->cols;
	}
	pnode = node;
	float* bdy_ptr = bdy->data.f32;
	assert(bdy->rows == a->rows - 1);
	for (i = 0; i < bdy->rows; i++)
	{
		for (j = 0; j < bdy->cols; j++)
		{
			mean += pedge->chi = bdy_ptr[j];
			pedge->node[0] = pnode + j;
			pedge->node[1] = pnode + a->cols + j;
			++pedge;
		}
		pnode += a->cols;
		bdy_ptr += bdy->cols;
	}
	assert(bdxy->rows == a->rows - 1 && bdxy->cols == a->cols - 1);
	pnode = node;
	float* bdxy_ptr = bdxy->data.f32;
	for (i = 0; i < bdxy->rows; i++)
	{
		for (j = 0; j < bdxy->cols; j++)
		{
			mean += pedge->chi = bdxy_ptr[j];
			pedge->node[0] = pnode + j;
			pedge->node[1] = pnode + a->cols + j + 1;
			++pedge;
		}
		pnode += a->cols;
		bdxy_ptr += bdxy->cols;
	}
	assert(bdxy2->rows == a->rows - 1 && bdxy2->cols == a->cols - 1);
	pnode = node;
	float* bdxy2_ptr = bdxy2->data.f32;
	for (i = 0; i < bdxy2->rows; i++)
	{
		for (j = 0; j < bdxy2->cols; j++)
		{
			mean += pedge->chi = bdxy2_ptr[j];
			pedge->node[0] = pnode + j + 1;
			pedge->node[1] = pnode + a->cols + j;
			++pedge;
		}
		pnode += a->cols;
		bdxy2_ptr += bdxy2->cols;
	}
	mean /= (double)(bdx->rows * bdx->cols + bdy->rows * bdy->cols + bdxy->rows * bdxy->cols + bdxy2->rows * bdxy2->cols);
	ccv_mscr_edge_t* edge_end = edge + bdx->rows * bdx->cols + bdy->rows * bdy->cols + bdxy->rows * bdxy->cols + bdxy2->rows * bdxy2->cols;
	ccv_matrix_free(bdx);
	ccv_matrix_free(bdy);
	ccv_matrix_free(bdxy);
	ccv_matrix_free(bdxy2);
	_ccv_mscr_edge_qsort(edge, edge_end - edge, 0);
	/* evolute on the edge graph */
	int seq_no = 0;
	pedge = edge;
	ccv_array_t* mscr_root_list = ccv_array_new(sizeof(ccv_mscr_root_t), 64, 0);
	ccv_array_t* mscr_area_list = ccv_array_new(sizeof(ccv_mscr_area_t), 64, 0);
	for (i = 0; (i < params.max_evolution) && (pedge < edge_end); i++)
	{
		double dk = (double)i / (double)params.max_evolution * (CHI_TABLE_SIZE - 1);
		int k = (int)dk;
		double rk = dk - k;
		double thres = mean * (chitab3[k] * (1.0 - rk) + chitab3[k + 1] * rk);
		// to process all the edges in the list that chi < thres
		while (pedge < edge_end && pedge->chi < thres)
		{
			ccv_mser_node_t* node0 = _ccv_mser_find_root(pedge->node[0]);
			ccv_mser_node_t* node1 = _ccv_mser_find_root(pedge->node[1]);
			if (node0 != node1)
			{
				ccv_mscr_root_t* root0 = (node0->root >= 0) ? (ccv_mscr_root_t*)ccv_array_get(mscr_root_list, node0->root) : 0;
				ccv_mscr_root_t* root1 = (node1->root >= 0) ? (ccv_mscr_root_t*)ccv_array_get(mscr_root_list, node1->root) : 0;
				// swap the node if root1 has higher rank, or larger in size, or root0 is non-existent
				if ((root0 && root1 && (root1->rank > root0->rank
										|| (root1->rank == root0->rank && root1->size > root0->size)))
					|| (root1 && !root0))
				{
					ccv_mser_node_t* node = node0;
					node0 = node1;
					node1 = node;
					ccv_mscr_root_t* root = root0;
					root0 = root1;
					root1 = root;
				}
				if (!root0)
				{
					ccv_mscr_root_t root;
					ccv_array_push(mscr_root_list, &root);
					root0 = (ccv_mscr_root_t*)ccv_array_get(mscr_root_list, mscr_root_list->rnum - 1);
					root1 = (node1->root >= 0) ? (ccv_mscr_root_t*)ccv_array_get(mscr_root_list, node1->root) : 0; // the memory may be reallocated
					node0->root = mscr_root_list->rnum - 1;
					_ccv_mscr_init_root(root0, node0);
				}
				++root0->rank;
				if (root1 && root1->last_mscr_area >= 0 && root0->last_mscr_area == -1)
					root0->last_mscr_area = root1->last_mscr_area;
				if (root0->step_now < i)
				/* faithful record the last size for area threshold check */
				{
					root0->last_size = root0->size;
					root0->step_now = i;
				}
				node1->shortcut = node0;
				if (root1)
				{
					root0->size += root1->size;
					root0->min_point.x = ccv_min(root0->min_point.x, root1->min_point.x);
					root0->min_point.y = ccv_min(root0->min_point.y, root1->min_point.y);
					root0->max_point.x = ccv_max(root0->max_point.x, root1->max_point.x);
					root0->max_point.y = ccv_max(root0->max_point.y, root1->max_point.y);
				} else {
					++root0->size;
					root0->min_point.x = ccv_min(root0->min_point.x, node1->point.x);
					root0->min_point.y = ccv_min(root0->min_point.y, node1->point.y);
					root0->max_point.x = ccv_max(root0->max_point.x, node1->point.x);
					root0->max_point.y = ccv_max(root0->max_point.y, node1->point.y);
				}
				/* insert one endless double link list to another, see illustration:
				 * 0->1->2->3->4->5->0
				 * a->b->c->d->a
				 * set 5.next (0.prev.next) point to a
				 * set 0.prev point to d
				 * set d.next (a.prev.next) point to 0
				 * set a.prev point to 5
				 * the result endless double link list will be:
				 * 0->1->2->3->4->5->a->b->c->d->0 */
				node0->prev->next = node1;
				ccv_mser_node_t* prev = node0->prev;
				node0->prev = node1->prev;
				node1->prev->next = node0; // consider self-referencing
				node1->prev = prev;
				if (root0->size > root0->last_size * params.area_threshold)
				// this is one condition check for Equation (10) */
				{
					if (root0->mscr_area >= 0)
					{
						ccv_mscr_area_t* mscr_area = (ccv_mscr_area_t*)ccv_array_get(mscr_area_list, root0->mscr_area);
						/* Page (4), compute the margin between the reinit point and before the next reinit point */
						mscr_area->margin = root0->chi - root0->prev_chi;
						if (mscr_area->margin > params.min_margin)
							mscr_area->seq_no = ++seq_no;
						root0->mscr_area = -1;
					}
					root0->prev_size = root0->size;
					root0->prev_chi = pedge->chi;
					root0->reinit = i;
					root0->min_slope = DBL_MAX;
				}
				root0->chi = pedge->chi;
				if (i > root0->reinit)
				{
					double slope = (double)(root0->size - root0->prev_size) / (root0->chi - root0->prev_chi);
					if (slope < root0->min_slope)
					{
						if (i > root0->reinit + 1 && root0->size >= params.min_area && root0->size <= params.max_area &&
							root0->max_point.y - root0->min_point.y > 1 && root0->max_point.x - root0->min_point.x > 1) // extreme rectangle rule
						{
							ccv_mscr_area_t* last_mscr_area = (root0->last_mscr_area >= 0) ? (ccv_mscr_area_t*)ccv_array_get(mscr_area_list, root0->last_mscr_area) : 0;
							if (!last_mscr_area || /* I added the diversity check for MSCR, as most MSER algorithm does */
								(double)(root0->size - last_mscr_area->size) / (double)last_mscr_area->size > params.min_diversity)
							{
								if (root0->mscr_area >= 0)
								{
									ccv_mscr_area_t* mscr_area = (ccv_mscr_area_t*)ccv_array_get(mscr_area_list, root0->mscr_area);
									mscr_area->head = node0;
									mscr_area->tail = node0->prev;
									mscr_area->margin = 0;
									mscr_area->size = root0->size;
									mscr_area->seq_no = 0;
								} else {
									ccv_mscr_area_t mscr_area = {
										.head = node0,
										.tail = node0->prev,
										.margin = 0,
										.size = root0->size,
										.seq_no = 0,
									};
									root0->mscr_area = root0->last_mscr_area = mscr_area_list->rnum;
									ccv_array_push(mscr_area_list, &mscr_area);
								}
							}
						}
						root0->min_slope = slope;
					}
				}
			}
			++pedge;
		}
	}
	ccv_array_free(mscr_root_list);
	assert(seq->rsize == sizeof(ccv_mser_keypoint_t));
	ccv_zero(b);
	unsigned char* b_ptr = b->data.u8;
#define for_block(_, _for_set, _for_get) \
	for (i = 0; i < mscr_area_list->rnum; i++) \
	{ \
		ccv_mscr_area_t* mscr_area = (ccv_mscr_area_t*)ccv_array_get(mscr_area_list, i); \
		if (mscr_area->seq_no > 0) \
		{ \
			ccv_mser_node_t* node = mscr_area->head; \
			ccv_mser_keypoint_t mser_keypoint = { \
				.size = mscr_area->size, \
				.keypoint = node->point, \
				.m10 = 0, .m01 = 0, .m11 = 0, \
				.m20 = 0, .m02 = 0, \
			}; \
			ccv_point_t min_point = node->point, \
						max_point = node->point; \
			for (j = 0; j < mscr_area->size; j++) \
			{ \
				if (_for_get(b_ptr + node->point.y * b->step, node->point.x, 0) == 0) \
					_for_set(b_ptr + node->point.y * b->step, node->point.x, mscr_area->seq_no, 0); \
				min_point.x = ccv_min(min_point.x, node->point.x); \
				min_point.y = ccv_min(min_point.y, node->point.y); \
				max_point.x = ccv_max(max_point.x, node->point.x); \
				max_point.y = ccv_max(max_point.y, node->point.y); \
				node = node->next; \
			} \
			assert(max_point.x - min_point.x > 1 && max_point.y - min_point.y > 1); \
			assert(node->prev == mscr_area->tail); /* endless double link list */ \
			mser_keypoint.rect = ccv_rect(min_point.x, min_point.y, max_point.x - min_point.x + 1, max_point.y - min_point.y + 1); \
			ccv_array_push(seq, &mser_keypoint); \
		} \
	}
	ccv_matrix_setter_getter(b->type, for_block);
#undef for_block
	ccv_array_free(mscr_area_list);
	ccfree(edge);
	ccfree(node);
}
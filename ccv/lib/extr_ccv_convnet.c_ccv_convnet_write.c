#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_14__ ;
typedef  struct TYPE_20__   TYPE_13__ ;
typedef  struct TYPE_19__   TYPE_12__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  int /*<<< orphan*/  layer_params_insert_qs ;
typedef  int /*<<< orphan*/  layer_data_insert_qs ;
typedef  int /*<<< orphan*/  convnet_params_insert_qs ;
struct TYPE_19__ {int half_precision; } ;
typedef  TYPE_12__ ccv_convnet_write_param_t ;
struct TYPE_24__ {int height; int width; } ;
struct TYPE_20__ {int count; int channels; TYPE_3__ input; TYPE_2__* mean_activity; TYPE_14__* layers; } ;
typedef  TYPE_13__ ccv_convnet_t ;
struct TYPE_29__ {int count; int relu; } ;
struct TYPE_28__ {int rows; int cols; int channels; int partition; int count; int strides; int border; } ;
struct TYPE_17__ {int size; int /*<<< orphan*/  beta; int /*<<< orphan*/  alpha; int /*<<< orphan*/  kappa; } ;
struct TYPE_30__ {int strides; int border; int size; } ;
struct TYPE_18__ {TYPE_8__ full_connect; TYPE_7__ convolutional; TYPE_10__ rnorm; TYPE_9__ pool; } ;
struct TYPE_26__ {int count; } ;
struct TYPE_25__ {int rows; int cols; int channels; int partition; } ;
struct TYPE_27__ {TYPE_5__ node; TYPE_4__ matrix; } ;
struct TYPE_21__ {int type; int wnum; TYPE_11__ net; int /*<<< orphan*/ * bias; int /*<<< orphan*/ * w; TYPE_6__ input; } ;
typedef  TYPE_14__ ccv_convnet_layer_t ;
struct TYPE_22__ {int /*<<< orphan*/ * f32; } ;
struct TYPE_23__ {int rows; int cols; TYPE_1__ data; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 scalar_t__ CCV_32F ; 
#define  CCV_CONVNET_AVERAGE_POOL 132 
#define  CCV_CONVNET_CONVOLUTIONAL 131 
#define  CCV_CONVNET_FULL_CONNECT 130 
#define  CCV_CONVNET_LOCAL_RESPONSE_NORM 129 
#define  CCV_CONVNET_MAX_POOL 128 
 int CCV_GET_CHANNEL (int /*<<< orphan*/ ) ; 
 scalar_t__ CCV_GET_DATA_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ SQLITE_DONE ; 
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ccfree ; 
 scalar_t__ ccmalloc (int) ; 
 int /*<<< orphan*/  ccv_float_to_half_precision (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_bind_blob (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_bind_double (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_bind_int (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  sqlite3_clear_bindings (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_close (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_exec (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_open (char const*,int /*<<< orphan*/ **) ; 
 scalar_t__ sqlite3_prepare_v2 (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_reset (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 

void ccv_convnet_write(ccv_convnet_t* convnet, const char* filename, ccv_convnet_write_param_t params)
{
	sqlite3* db = 0;
	if (SQLITE_OK == sqlite3_open(filename, &db))
	{
		const char layer_create_table_qs[] =
			"CREATE TABLE IF NOT EXISTS layer_params "
			"(layer INTEGER PRIMARY KEY ASC, type INTEGER, "
			"input_matrix_rows INTEGER, input_matrix_cols INTEGER, input_matrix_channels INTEGER, input_matrix_partition INTEGER, input_node_count INTEGER, "
			"output_rows INTEGER, output_cols INTEGER, output_channels INTEGER, output_partition INTEGER, output_count INTEGER, output_strides INTEGER, output_border INTEGER, "
			"output_size INTEGER, output_kappa REAL, output_alpha REAL, output_beta REAL, output_relu INTEGER);"
			"CREATE TABLE IF NOT EXISTS convnet_params "
			"(convnet INTEGER PRIMARY KEY ASC, input_height INTEGER, input_width INTEGER, mean_activity BLOB);"
			"CREATE TABLE IF NOT EXISTS layer_data "
			"(layer INTEGER PRIMARY KEY ASC, weight BLOB, bias BLOB, half_precision INTEGER);";
		assert(SQLITE_OK == sqlite3_exec(db, layer_create_table_qs, 0, 0, 0));
		const char layer_params_insert_qs[] = 
			"REPLACE INTO layer_params "
			"(layer, type, "
			"input_matrix_rows, input_matrix_cols, input_matrix_channels, input_matrix_partition, input_node_count, "
			"output_rows, output_cols, output_channels, output_partition, output_count, output_strides, output_border, "
			"output_size, output_kappa, output_alpha, output_beta, output_relu) VALUES "
			"($layer, $type, " // 1
			"$input_matrix_rows, $input_matrix_cols, $input_matrix_channels, $input_matrix_partition, $input_node_count, " // 6
			"$output_rows, $output_cols, $output_channels, $output_partition, $output_count, $output_strides, $output_border, " // 13
			"$output_size, $output_kappa, $output_alpha, $output_beta, $output_relu);"; // 18
		sqlite3_stmt* layer_params_insert_stmt = 0;
		assert(SQLITE_OK == sqlite3_prepare_v2(db, layer_params_insert_qs, sizeof(layer_params_insert_qs), &layer_params_insert_stmt, 0));
		const char layer_data_insert_qs[] =
			"REPLACE INTO layer_data "
			"(layer, weight, bias, half_precision) VALUES ($layer, $weight, $bias, $half_precision);";
		sqlite3_stmt* layer_data_insert_stmt = 0;
		assert(SQLITE_OK == sqlite3_prepare_v2(db, layer_data_insert_qs, sizeof(layer_data_insert_qs), &layer_data_insert_stmt, 0));
		int i;
		for (i = 0; i < convnet->count; i++)
		{
			ccv_convnet_layer_t* layer = convnet->layers + i;
			// insert layer params
			sqlite3_bind_int(layer_params_insert_stmt, 1, i);
			sqlite3_bind_int(layer_params_insert_stmt, 2, layer->type);
			sqlite3_bind_int(layer_params_insert_stmt, 3, layer->input.matrix.rows);
			sqlite3_bind_int(layer_params_insert_stmt, 4, layer->input.matrix.cols);
			sqlite3_bind_int(layer_params_insert_stmt, 5, layer->input.matrix.channels);
			sqlite3_bind_int(layer_params_insert_stmt, 6, layer->input.matrix.partition);
			sqlite3_bind_int(layer_params_insert_stmt, 7, layer->input.node.count);
			switch (layer->type)
			{
				case CCV_CONVNET_CONVOLUTIONAL:
					sqlite3_bind_int(layer_params_insert_stmt, 8, layer->net.convolutional.rows);
					sqlite3_bind_int(layer_params_insert_stmt, 9, layer->net.convolutional.cols);
					sqlite3_bind_int(layer_params_insert_stmt, 10, layer->net.convolutional.channels);
					sqlite3_bind_int(layer_params_insert_stmt, 11, layer->net.convolutional.partition);
					sqlite3_bind_int(layer_params_insert_stmt, 12, layer->net.convolutional.count);
					sqlite3_bind_int(layer_params_insert_stmt, 13, layer->net.convolutional.strides);
					sqlite3_bind_int(layer_params_insert_stmt, 14, layer->net.convolutional.border);
					break;
				case CCV_CONVNET_FULL_CONNECT:
					sqlite3_bind_int(layer_params_insert_stmt, 12, layer->net.full_connect.count);
					sqlite3_bind_int(layer_params_insert_stmt, 19, layer->net.full_connect.relu);
					break;
				case CCV_CONVNET_MAX_POOL:
				case CCV_CONVNET_AVERAGE_POOL:
					sqlite3_bind_int(layer_params_insert_stmt, 13, layer->net.pool.strides);
					sqlite3_bind_int(layer_params_insert_stmt, 14, layer->net.pool.border);
					sqlite3_bind_int(layer_params_insert_stmt, 15, layer->net.pool.size);
					break;
				case CCV_CONVNET_LOCAL_RESPONSE_NORM:
					sqlite3_bind_int(layer_params_insert_stmt, 15, layer->net.rnorm.size);
					sqlite3_bind_double(layer_params_insert_stmt, 16, layer->net.rnorm.kappa);
					sqlite3_bind_double(layer_params_insert_stmt, 17, layer->net.rnorm.alpha);
					sqlite3_bind_double(layer_params_insert_stmt, 18, layer->net.rnorm.beta);
					break;
			}
			assert(SQLITE_DONE == sqlite3_step(layer_params_insert_stmt));
			sqlite3_reset(layer_params_insert_stmt);
			sqlite3_clear_bindings(layer_params_insert_stmt);
			// insert layer data
			if (layer->type == CCV_CONVNET_CONVOLUTIONAL || layer->type == CCV_CONVNET_FULL_CONNECT)
			{
				sqlite3_bind_int(layer_data_insert_stmt, 1, i);
				if (params.half_precision)
				{
					uint16_t* w = (uint16_t*)ccmalloc(sizeof(uint16_t) * layer->wnum);
					ccv_float_to_half_precision(layer->w, w, layer->wnum);
					uint16_t* bias = (uint16_t*)ccmalloc(sizeof(uint16_t) * (layer->type == CCV_CONVNET_CONVOLUTIONAL ? layer->net.convolutional.count : layer->net.full_connect.count));
					ccv_float_to_half_precision(layer->bias, bias, layer->type == CCV_CONVNET_CONVOLUTIONAL ? layer->net.convolutional.count : layer->net.full_connect.count);
					sqlite3_bind_blob(layer_data_insert_stmt, 2, w, sizeof(uint16_t) * layer->wnum, ccfree);
					sqlite3_bind_blob(layer_data_insert_stmt, 3, bias, sizeof(uint16_t) * (layer->type == CCV_CONVNET_CONVOLUTIONAL ? layer->net.convolutional.count : layer->net.full_connect.count), ccfree);
				} else {
					sqlite3_bind_blob(layer_data_insert_stmt, 2, layer->w, sizeof(float) * layer->wnum, SQLITE_STATIC);
					sqlite3_bind_blob(layer_data_insert_stmt, 3, layer->bias, sizeof(float) * (layer->type == CCV_CONVNET_CONVOLUTIONAL ? layer->net.convolutional.count : layer->net.full_connect.count), SQLITE_STATIC);
				}
				sqlite3_bind_int(layer_data_insert_stmt, 4, params.half_precision);
				assert(SQLITE_DONE == sqlite3_step(layer_data_insert_stmt));
				sqlite3_reset(layer_data_insert_stmt);
				sqlite3_clear_bindings(layer_data_insert_stmt);
			}
		}
		// insert convnet related params
		const char convnet_params_insert_qs[] =
			"REPLACE INTO convnet_params "
			"(convnet, mean_activity, input_height, input_width) VALUES (0, $mean_activity, $input_height, $input_width);";
		sqlite3_stmt* convnet_params_insert_stmt = 0;
		assert(SQLITE_OK == sqlite3_prepare_v2(db, convnet_params_insert_qs, sizeof(convnet_params_insert_qs), &convnet_params_insert_stmt, 0));
		assert(convnet->mean_activity->rows == convnet->input.height);
		assert(convnet->mean_activity->cols == convnet->input.width);
		assert(CCV_GET_CHANNEL(convnet->mean_activity->type) == convnet->channels);
		assert(CCV_GET_DATA_TYPE(convnet->mean_activity->type) == CCV_32F);
		sqlite3_bind_blob(convnet_params_insert_stmt, 1, convnet->mean_activity->data.f32, sizeof(float) * convnet->input.height * convnet->input.width * convnet->channels, SQLITE_STATIC);
		sqlite3_bind_int(convnet_params_insert_stmt, 2, convnet->input.height);
		sqlite3_bind_int(convnet_params_insert_stmt, 3, convnet->input.width);
		assert(SQLITE_DONE == sqlite3_step(convnet_params_insert_stmt));
		sqlite3_reset(convnet_params_insert_stmt);
		sqlite3_clear_bindings(convnet_params_insert_stmt);

		sqlite3_finalize(layer_params_insert_stmt);
		sqlite3_finalize(layer_data_insert_stmt);
		sqlite3_finalize(convnet_params_insert_stmt);
		sqlite3_close(db);
	}
}
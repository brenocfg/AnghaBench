#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_size; } ;
struct fast_task_info {scalar_t__ arg; } ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  decode_buff ;
struct TYPE_9__ {char** paths; } ;
struct TYPE_7__ {int /*<<< orphan*/  filename; int /*<<< orphan*/  fname2log; } ;
struct TYPE_8__ {TYPE_2__ file_context; } ;
struct TYPE_6__ {int storage_id; int /*<<< orphan*/  mtime; int /*<<< orphan*/  fsize; } ;
typedef  TYPE_1__ StorageFileInfoForCRC32 ;
typedef  TYPE_2__ StorageFileContext ;
typedef  TYPE_3__ StorageClientInfo ;

/* Variables and functions */
 int /*<<< orphan*/  FDFS_FILENAME_BASE64_LENGTH ; 
 int FDFS_LOGIC_FILE_PATH_LEN ; 
 scalar_t__ IS_APPENDER_FILE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  base64_decode_auto (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,char*,int*) ; 
 int buff2int (char*) ; 
 int /*<<< orphan*/  buff2long (char*) ; 
 int /*<<< orphan*/  calc_crc32_done_callback_for_query_finfo ; 
 int /*<<< orphan*/  g_fdfs_base64_context ; 
 TYPE_5__ g_fdfs_store_paths ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int ntohl (int) ; 
 int push_calc_crc32_to_dio_queue (struct fast_task_info*,int /*<<< orphan*/ ,int const,struct stat*,int) ; 
 int query_file_info_response (struct fast_task_info*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char const*,...) ; 

__attribute__((used)) static int query_file_info_deal_response(struct fast_task_info *pTask,
        const char *filename, const char *true_filename,
        struct stat *file_stat, const int store_path_index)
{
	char decode_buff[64];
	int buff_len;
    int storage_id;
    int crc32;
    int64_t file_size;
    StorageFileInfoForCRC32 finfo;

	memset(decode_buff, 0, sizeof(decode_buff));
	base64_decode_auto(&g_fdfs_base64_context, filename +
		FDFS_LOGIC_FILE_PATH_LEN, FDFS_FILENAME_BASE64_LENGTH,
		decode_buff, &buff_len);
	storage_id = ntohl(buff2int(decode_buff));
	file_size = buff2long(decode_buff + sizeof(int) * 2);
	if (IS_APPENDER_FILE(file_size))
    {
        StorageClientInfo *pClientInfo;
        StorageFileContext *pFileContext;

        pClientInfo = (StorageClientInfo *)pTask->arg;
        pFileContext =  &(pClientInfo->file_context);

        snprintf(pFileContext->fname2log, sizeof(pFileContext->fname2log),
                "%s", filename);
        snprintf(pFileContext->filename, sizeof(pFileContext->filename),
                "%s/data/%s", g_fdfs_store_paths.paths[store_path_index],
                true_filename);

        return push_calc_crc32_to_dio_queue(pTask,
                calc_crc32_done_callback_for_query_finfo,
                store_path_index, file_stat, storage_id);
    }

    finfo.storage_id = storage_id;
    finfo.fsize = file_stat->st_size;
    finfo.mtime = file_stat->st_mtime;
	crc32 = buff2int(decode_buff + sizeof(int) * 4);
    return query_file_info_response(pTask, &finfo, crc32);
}
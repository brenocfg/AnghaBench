#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct AVTreeNode {scalar_t__ logical_pos; int size; scalar_t__ physical_pos; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_5__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_6__ {scalar_t__ logical_pos; int /*<<< orphan*/  root; scalar_t__ cache_pos; int /*<<< orphan*/  fd; } ;
typedef  TYPE_2__ Context ;
typedef  struct AVTreeNode CacheEntry ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  av_free (struct AVTreeNode*) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 struct AVTreeNode* av_malloc (int) ; 
 struct AVTreeNode* av_tree_find (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,void**) ; 
 struct AVTreeNode* av_tree_insert (int /*<<< orphan*/ *,struct AVTreeNode*,int /*<<< orphan*/ ,struct AVTreeNode**) ; 
 struct AVTreeNode* av_tree_node_alloc () ; 
 int /*<<< orphan*/  cmp ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int write (int /*<<< orphan*/ ,unsigned char const*,int) ; 

__attribute__((used)) static int add_entry(URLContext *h, const unsigned char *buf, int size)
{
    Context *c= h->priv_data;
    int64_t pos = -1;
    int ret;
    CacheEntry *entry = NULL, *next[2] = {NULL, NULL};
    CacheEntry *entry_ret;
    struct AVTreeNode *node = NULL;

    //FIXME avoid lseek
    pos = lseek(c->fd, 0, SEEK_END);
    if (pos < 0) {
        ret = AVERROR(errno);
        av_log(h, AV_LOG_ERROR, "seek in cache failed\n");
        goto fail;
    }
    c->cache_pos = pos;

    ret = write(c->fd, buf, size);
    if (ret < 0) {
        ret = AVERROR(errno);
        av_log(h, AV_LOG_ERROR, "write in cache failed\n");
        goto fail;
    }
    c->cache_pos += ret;

    entry = av_tree_find(c->root, &c->logical_pos, cmp, (void**)next);

    if (!entry)
        entry = next[0];

    if (!entry ||
        entry->logical_pos  + entry->size != c->logical_pos ||
        entry->physical_pos + entry->size != pos
    ) {
        entry = av_malloc(sizeof(*entry));
        node = av_tree_node_alloc();
        if (!entry || !node) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }
        entry->logical_pos = c->logical_pos;
        entry->physical_pos = pos;
        entry->size = ret;

        entry_ret = av_tree_insert(&c->root, entry, cmp, &node);
        if (entry_ret && entry_ret != entry) {
            ret = -1;
            av_log(h, AV_LOG_ERROR, "av_tree_insert failed\n");
            goto fail;
        }
    } else
        entry->size += ret;

    return 0;
fail:
    //we could truncate the file to pos here if pos >=0 but ftruncate isn't available in VS so
    //for simplicty we just leave the file a bit larger
    av_free(entry);
    av_free(node);
    return ret;
}
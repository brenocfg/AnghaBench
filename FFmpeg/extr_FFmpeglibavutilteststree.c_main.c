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
typedef  int /*<<< orphan*/  AVTreeNode ;
typedef  int /*<<< orphan*/  AVLFG ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_LOG_INFO ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 int av_lfg_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_lfg_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  av_log_set_level (int) ; 
 int /*<<< orphan*/  av_tree_destroy (int /*<<< orphan*/ *) ; 
 void* av_tree_find (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_tree_insert (int /*<<< orphan*/ **,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * av_tree_node_alloc () ; 
 int check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmp ; 
 int /*<<< orphan*/  print (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int main(int argc, char **argv)
{
    int i;
    void *k;
    AVTreeNode *root = NULL, *node = NULL;
    AVLFG prng;
    int log_level = argc <= 1 ? AV_LOG_INFO : atoi(argv[1]);

    av_log_set_level(log_level);

    av_lfg_init(&prng, 1);

    for (i = 0; i < 10000; i++) {
        intptr_t j = av_lfg_get(&prng) % 86294;

        if (check(root) > 999) {
            av_log(NULL, AV_LOG_ERROR, "FATAL error %d\n", i);
            print(root, 0);
            return 1;
        }
        av_log(NULL, AV_LOG_DEBUG, "inserting %4d\n", (int)j);

        if (!node)
            node = av_tree_node_alloc();
        if (!node) {
            av_log(NULL, AV_LOG_ERROR, "Memory allocation failure.\n");
            return 1;
        }
        av_tree_insert(&root, (void *)(j + 1), cmp, &node);

        j = av_lfg_get(&prng) % 86294;
        {
            AVTreeNode *node2 = NULL;
            av_log(NULL, AV_LOG_DEBUG, "removing %4d\n", (int)j);
            av_tree_insert(&root, (void *)(j + 1), cmp, &node2);
            k = av_tree_find(root, (void *)(j + 1), cmp, NULL);
            if (k)
                av_log(NULL, AV_LOG_ERROR, "removal failure %d\n", i);
            av_free(node2);
        }
    }
    av_free(node);

    av_tree_destroy(root);

    return 0;
}
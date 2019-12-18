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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct color_rect {int* max; int* min; } ;
struct color_node {int split; int palette_id; int* val; int left_id; int right_id; } ;

/* Variables and functions */
 int get_next_color (int*,int const*,int const,int*,struct color_rect const*) ; 

__attribute__((used)) static int colormap_insert(struct color_node *map,
                           uint8_t *color_used,
                           int *nb_used,
                           const uint32_t *palette,
                           const int trans_thresh,
                           const struct color_rect *box)
{
    uint32_t c;
    int component, cur_id;
    int node_left_id = -1, node_right_id = -1;
    struct color_node *node;
    struct color_rect box1, box2;
    const int pal_id = get_next_color(color_used, palette, trans_thresh, &component, box);

    if (pal_id < 0)
        return -1;

    /* create new node with that color */
    cur_id = (*nb_used)++;
    c = palette[pal_id];
    node = &map[cur_id];
    node->split = component;
    node->palette_id = pal_id;
    node->val[0] = c>>24 & 0xff;
    node->val[1] = c>>16 & 0xff;
    node->val[2] = c>> 8 & 0xff;
    node->val[3] = c     & 0xff;

    color_used[pal_id] = 1;

    /* get the two boxes this node creates */
    box1 = box2 = *box;
    box1.max[component-1] = node->val[component];
    box2.min[component-1] = node->val[component] + 1;

    node_left_id = colormap_insert(map, color_used, nb_used, palette, trans_thresh, &box1);

    if (box2.min[component-1] <= box2.max[component-1])
        node_right_id = colormap_insert(map, color_used, nb_used, palette, trans_thresh, &box2);

    node->left_id  = node_left_id;
    node->right_id = node_right_id;

    return cur_id;
}
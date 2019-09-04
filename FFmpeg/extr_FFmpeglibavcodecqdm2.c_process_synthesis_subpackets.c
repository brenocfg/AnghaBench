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
typedef  int /*<<< orphan*/  QDM2SubPNode ;
typedef  int /*<<< orphan*/  QDM2Context ;

/* Variables and functions */
 int /*<<< orphan*/  process_subpacket_10 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_subpacket_11 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_subpacket_12 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_subpacket_9 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * qdm2_search_subpacket_type_in_list (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void process_synthesis_subpackets(QDM2Context *q, QDM2SubPNode *list)
{
    QDM2SubPNode *nodes[4];

    nodes[0] = qdm2_search_subpacket_type_in_list(list, 9);
    if (nodes[0])
        process_subpacket_9(q, nodes[0]);

    nodes[1] = qdm2_search_subpacket_type_in_list(list, 10);
    if (nodes[1])
        process_subpacket_10(q, nodes[1]);
    else
        process_subpacket_10(q, NULL);

    nodes[2] = qdm2_search_subpacket_type_in_list(list, 11);
    if (nodes[0] && nodes[1] && nodes[2])
        process_subpacket_11(q, nodes[2]);
    else
        process_subpacket_11(q, NULL);

    nodes[3] = qdm2_search_subpacket_type_in_list(list, 12);
    if (nodes[0] && nodes[1] && nodes[3])
        process_subpacket_12(q, nodes[3]);
    else
        process_subpacket_12(q, NULL);
}
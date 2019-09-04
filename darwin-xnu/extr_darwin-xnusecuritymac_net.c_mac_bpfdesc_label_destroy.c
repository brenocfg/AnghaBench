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
struct label {int dummy; } ;
struct bpf_d {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mac_bpfdesc_label_free (struct label*) ; 
 struct label* mac_bpfdesc_label_get (struct bpf_d*) ; 
 int /*<<< orphan*/  mac_bpfdesc_label_set (struct bpf_d*,int /*<<< orphan*/ *) ; 

void
mac_bpfdesc_label_destroy(struct bpf_d *bpf_d)
{
	struct label *label;

	label = mac_bpfdesc_label_get(bpf_d);
	mac_bpfdesc_label_free(label);
	mac_bpfdesc_label_set(bpf_d, NULL);
}
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
struct kvm_kpit_state {int speaker_data_on; int /*<<< orphan*/  lock; } ;
struct kvm_pit {struct kvm* kvm; struct kvm_kpit_state pit_state; } ;
struct kvm_io_device {int dummy; } ;
struct kvm {int dummy; } ;
typedef  int /*<<< orphan*/  ret ;
typedef  scalar_t__ gpa_t ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ KVM_SPEAKER_BASE_ADDRESS ; 
 int /*<<< orphan*/  ktime_get () ; 
 scalar_t__ ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pit_get_gate (struct kvm*,int) ; 
 int pit_get_out (struct kvm*,int) ; 
 struct kvm_pit* speaker_to_pit (struct kvm_io_device*) ; 

__attribute__((used)) static int speaker_ioport_read(struct kvm_io_device *this,
			       gpa_t addr, int len, void *data)
{
	struct kvm_pit *pit = speaker_to_pit(this);
	struct kvm_kpit_state *pit_state = &pit->pit_state;
	struct kvm *kvm = pit->kvm;
	unsigned int refresh_clock;
	int ret;
	if (addr != KVM_SPEAKER_BASE_ADDRESS)
		return -EOPNOTSUPP;

	/* Refresh clock toggles at about 15us. We approximate as 2^14ns. */
	refresh_clock = ((unsigned int)ktime_to_ns(ktime_get()) >> 14) & 1;

	mutex_lock(&pit_state->lock);
	ret = ((pit_state->speaker_data_on << 1) | pit_get_gate(kvm, 2) |
		(pit_get_out(kvm, 2) << 5) | (refresh_clock << 4));
	if (len > sizeof(ret))
		len = sizeof(ret);
	memcpy(data, (char *)&ret, len);
	mutex_unlock(&pit_state->lock);
	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct gpio_key_state {int debounce; struct gpio_input_state* ds; } ;
struct gpio_input_state {TYPE_1__* info; int /*<<< orphan*/  input_dev; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  timer; int /*<<< orphan*/  wake_lock; int /*<<< orphan*/  debounce_count; int /*<<< orphan*/  use_irq; struct gpio_key_state* key_state; } ;
struct gpio_event_direct_entry {int /*<<< orphan*/  code; int /*<<< orphan*/  gpio; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {scalar_t__ tv64; } ;
struct TYPE_3__ {int flags; int /*<<< orphan*/  type; TYPE_2__ debounce_time; struct gpio_event_direct_entry* keymap; } ;

/* Variables and functions */
 int DEBOUNCE_UNKNOWN ; 
 int DEBOUNCE_UNSTABLE ; 
 int DEBOUNCE_WAIT_IRQ ; 
 int GPIOEDF_ACTIVE_HIGH ; 
 int GPIOEDF_PRINT_KEYS ; 
 int GPIOEDF_PRINT_KEY_DEBOUNCE ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  disable_irq (int) ; 
 int gpio_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,TYPE_2__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t gpio_event_input_irq_handler(int irq, void *dev_id)
{
	struct gpio_key_state *ks = dev_id;
	struct gpio_input_state *ds = ks->ds;
	int keymap_index = ks - ds->key_state;
	const struct gpio_event_direct_entry *key_entry;
	unsigned long irqflags;
	int pressed;

	if (!ds->use_irq)
		return IRQ_HANDLED;

	key_entry = &ds->info->keymap[keymap_index];

	if (ds->info->debounce_time.tv64) {
		spin_lock_irqsave(&ds->irq_lock, irqflags);
		if (ks->debounce & DEBOUNCE_WAIT_IRQ) {
			ks->debounce = DEBOUNCE_UNKNOWN;
			if (ds->debounce_count++ == 0) {
				wake_lock(&ds->wake_lock);
				hrtimer_start(
					&ds->timer, ds->info->debounce_time,
					HRTIMER_MODE_REL);
			}
			if (ds->info->flags & GPIOEDF_PRINT_KEY_DEBOUNCE)
				pr_info("gpio_event_input_irq_handler: "
					"key %x-%x, %d (%d) start debounce\n",
					ds->info->type, key_entry->code,
					keymap_index, key_entry->gpio);
		} else {
			disable_irq(irq);
			ks->debounce = DEBOUNCE_UNSTABLE;
		}
		spin_unlock_irqrestore(&ds->irq_lock, irqflags);
	} else {
		pressed = gpio_get_value(key_entry->gpio) ^
			!(ds->info->flags & GPIOEDF_ACTIVE_HIGH);
		if (ds->info->flags & GPIOEDF_PRINT_KEYS)
			pr_info("gpio_event_input_irq_handler: key %x-%x, %d "
				"(%d) changed to %d\n",
				ds->info->type, key_entry->code, keymap_index,
				key_entry->gpio, pressed);
		input_event(ds->input_dev, ds->info->type,
			    key_entry->code, pressed);
	}
	return IRQ_HANDLED;
}
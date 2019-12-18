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
struct mimio {scalar_t__ open; scalar_t__ present; } ;
struct input_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct mimio* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  mimio_dealloc (struct mimio*) ; 

__attribute__((used)) static void mimio_close(struct input_dev *idev)
{
	struct mimio *mimio;

	mimio = input_get_drvdata(idev);
	if (!mimio) {
		dev_err(&idev->dev, "null mimio attached to input device\n");
		return;
	}

	if (mimio->open <= 0)
		dev_err(&idev->dev, "mimio not open.\n");
	else
		mimio->open--;

	if (mimio->present == 0 && mimio->open == 0)
		mimio_dealloc(mimio);
}
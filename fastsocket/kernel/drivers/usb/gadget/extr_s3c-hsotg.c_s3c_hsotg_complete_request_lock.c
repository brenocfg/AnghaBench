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
struct s3c_hsotg_req {int dummy; } ;
struct s3c_hsotg_ep {int /*<<< orphan*/  lock; } ;
struct s3c_hsotg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  s3c_hsotg_complete_request (struct s3c_hsotg*,struct s3c_hsotg_ep*,struct s3c_hsotg_req*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void s3c_hsotg_complete_request_lock(struct s3c_hsotg *hsotg,
					    struct s3c_hsotg_ep *hs_ep,
					    struct s3c_hsotg_req *hs_req,
					    int result)
{
	unsigned long flags;

	spin_lock_irqsave(&hs_ep->lock, flags);
	s3c_hsotg_complete_request(hsotg, hs_ep, hs_req, result);
	spin_unlock_irqrestore(&hs_ep->lock, flags);
}
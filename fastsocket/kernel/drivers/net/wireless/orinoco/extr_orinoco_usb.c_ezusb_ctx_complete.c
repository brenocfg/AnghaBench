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
struct request_context {int state; int /*<<< orphan*/  done; int /*<<< orphan*/  out_rid; int /*<<< orphan*/  list; struct ezusb_priv* upriv; } ;
struct net_device_stats {int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_errors; } ;
struct orinoco_private {struct net_device_stats stats; } ;
struct net_device {int dummy; } ;
struct ezusb_priv {scalar_t__ udev; int /*<<< orphan*/  req_lock; struct net_device* dev; } ;

/* Variables and functions */
#define  EZUSB_CTX_COMPLETE 132 
#define  EZUSB_CTX_REQSUBMIT_FAIL 131 
#define  EZUSB_CTX_REQ_FAILED 130 
#define  EZUSB_CTX_REQ_TIMEOUT 129 
#define  EZUSB_CTX_RESP_TIMEOUT 128 
 int /*<<< orphan*/  EZUSB_RID_TX ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  ezusb_complete_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ezusb_req_queue_run (struct ezusb_priv*) ; 
 int /*<<< orphan*/  ezusb_request_context_put (struct request_context*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 struct orinoco_private* ndev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ezusb_ctx_complete(struct request_context *ctx)
{
	struct ezusb_priv *upriv = ctx->upriv;
	unsigned long flags;

	spin_lock_irqsave(&upriv->req_lock, flags);

	list_del_init(&ctx->list);
	if (upriv->udev) {
		spin_unlock_irqrestore(&upriv->req_lock, flags);
		ezusb_req_queue_run(upriv);
		spin_lock_irqsave(&upriv->req_lock, flags);
	}

	switch (ctx->state) {
	case EZUSB_CTX_COMPLETE:
	case EZUSB_CTX_REQSUBMIT_FAIL:
	case EZUSB_CTX_REQ_FAILED:
	case EZUSB_CTX_REQ_TIMEOUT:
	case EZUSB_CTX_RESP_TIMEOUT:
		spin_unlock_irqrestore(&upriv->req_lock, flags);

		if ((ctx->out_rid == EZUSB_RID_TX) && upriv->dev) {
			struct net_device *dev = upriv->dev;
			struct orinoco_private *priv = ndev_priv(dev);
			struct net_device_stats *stats = &priv->stats;

			if (ctx->state != EZUSB_CTX_COMPLETE)
				stats->tx_errors++;
			else
				stats->tx_packets++;

			netif_wake_queue(dev);
		}
		ezusb_complete_all(&ctx->done);
		ezusb_request_context_put(ctx);
		break;

	default:
		spin_unlock_irqrestore(&upriv->req_lock, flags);
		if (!upriv->udev) {
			/* This is normal, as all request contexts get flushed
			 * when the device is disconnected */
			err("Called, CTX not terminating, but device gone");
			ezusb_complete_all(&ctx->done);
			ezusb_request_context_put(ctx);
			break;
		}

		err("Called, CTX not in terminating state.");
		/* Things are really bad if this happens. Just leak
		 * the CTX because it may still be linked to the
		 * queue or the OUT urb may still be active.
		 * Just leaking at least prevents an Oops or Panic.
		 */
		break;
	}
}
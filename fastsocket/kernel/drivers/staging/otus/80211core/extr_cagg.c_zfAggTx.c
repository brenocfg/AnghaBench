#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  zbuf_t ;
typedef  int u16_t ;
struct TYPE_2__ {int /*<<< orphan*/  aggInitiated; } ;
typedef  int /*<<< orphan*/ * TID_TX ;

/* Variables and functions */
 int ZM_ERR_TX_BUFFER_UNAVAILABLE ; 
 TYPE_1__* wd ; 
 int zfAggGetSta (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zfAggTxEnqueue (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zfAggTxGetQueue (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * zfAggTxNewQueue (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

u16_t zfAggTx(zdev_t* dev, zbuf_t* buf, u16_t tid)
{
    u16_t aid;
    //u16_t qnum;
    //u16_t aggflag = 0;
    //u16_t arrivalrate = 0;
    TID_TX tid_tx;

    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();

    if(!wd->aggInitiated)
    {
        return ZM_ERR_TX_BUFFER_UNAVAILABLE;
    }

    aid = zfAggGetSta(dev, buf);

    //arrivalrate = zfAggTxArrivalRate(dev, aid, tid);

    if (0xffff == aid)
    {
        /*
         * STA not associated, this is a BC/MC or STA->AP packet
         */

        return ZM_ERR_TX_BUFFER_UNAVAILABLE;
    }

    /*
     * STA associated, a unicast packet
     */

    tid_tx = zfAggTxGetQueue(dev, aid, tid);

    /*tid_q.tid_tx = tid_tx;
    wd->destQ.insert = zfAggDestInsert;
    wd->destQ.insert(dev, 0, tid_q);
    */
    if (tid_tx != NULL)
    {
        /*
         * this (aid, ac) is aggregated
         */

        //if (arrivalrate < ZM_AGG_LOW_THRESHOLD)
        if (0)
        {
            /*
             * arrival rate too low
             * delete this aggregate queue
             */

            zmw_enter_critical_section(dev);

            //wd->aggQPool[qnum]->clearFlag = wd->aggQPool[qnum]->deleteFlag =1;

            zmw_leave_critical_section(dev);

        }

        return zfAggTxEnqueue(dev, buf, aid, tid_tx);

    }
    else
    {
        /*
         * this (aid, ac) not yet aggregated
         * queue not found
         */

        //if (arrivalrate > ZM_AGG_HIGH_THRESHOLD)
        if (1)
        {
            /*
             * arrivalrate high enough to get a new agg queue
             */

            tid_tx = zfAggTxNewQueue(dev, aid, tid, buf);

            //zm_msg1_agg(ZM_LV_0, "get new AggQueue qnum = ", tid_tx->);

            if (tid_tx)
            {
                /*
                 * got a new aggregate queue
                 */

                //zmw_enter_critical_section(dev);

                //wd->aggSta[aid].aggFlag[ac] = 1;

                //zmw_leave_critical_section(dev);

                /*
                 * add ADDBA functions here
                 * return ZM_ERR_TX_BUFFER_UNAVAILABLE;
                 */


                //zfAggSendAddbaRequest(dev, tid_tx->dst, tid_tx->ac, tid_tx->tid);
                //zmw_enter_critical_section(dev);

                //wd->aggSta[aid].aggFlag[ac] = 0;

                //zmw_leave_critical_section(dev);

                return zfAggTxEnqueue(dev, buf, aid, tid_tx);

            }
            else
            {
                /*
                 * just can't get a new aggregate queue
                 */

                return ZM_ERR_TX_BUFFER_UNAVAILABLE;
            }
        }
        else
        {
            /*
             * arrival rate is not high enough to get a new agg queue
             */

            return ZM_ERR_TX_BUFFER_UNAVAILABLE;
        }
    }



}
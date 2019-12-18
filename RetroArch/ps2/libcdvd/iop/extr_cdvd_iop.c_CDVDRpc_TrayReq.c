void *CDVDRpc_TrayReq(unsigned int *sbuff)
{
    int ret;

    sceCdTrayReq(sbuff[0], (int *)&ret);

    sbuff[0] = ret;
    return sbuff;
}
void *CDVDRpc_GetSize(unsigned int *sbuff)
{
    sbuff[0] = CdGetSize();
    return sbuff;
}